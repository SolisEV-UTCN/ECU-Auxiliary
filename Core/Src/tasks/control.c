#include "main.h"

extern CAN_HandleTypeDef hcan;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

bool Toggle_State_Right = OFF;
bool Toggle_State_Left = OFF;
bool Offline_Mode_Switch = OFF;

/* Blinker toggle counters: count to 6 (*76ms) for ~500ms blink period */
uint8_t Sign_Left_500ms_Timer = 0;
uint8_t Sign_Right_500ms_Timer = 0;

/* Dashboard watchdog counter, incremented every 56ms by TIM2 */
uint8_t Dash_Activity = 0;

aux_state Offline = {.state = 0x00};
aux_state *Offline_Mode = &Offline;

aux_state aux = {.state = 0x00};
aux_state *auxiliary = &aux;

/*
 * TIM2 ISR (56ms period)
 * Reads the offline mode switch and increments the dashboard watchdog.
 * If Dash_Activity reaches 100 (~5.6s) without a CAN reset, dashboard is considered lost.
 */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

	Offline_Mode_Switch = HAL_GPIO_ReadPin(GPIOA, ENABLE_OFFLINE_MODE_Pin);

	if (Dash_Activity <= 100 && Offline_Mode_Switch == OFF)
	{
		Dash_Activity++;
	}

  /* USER CODE END TIM2_IRQn 1 */
}

/*
 * TIM3 ISR (76ms period)
 * Enables power output after ~2s startup delay, then continuously
 * updates GPIO outputs and sends the CAN alive frame.
 */
static uint8_t timer;
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
	if (++timer == 26) // ~2 seconds startup delay
		HAL_GPIO_WritePin(GPIOB, ENABLE_POWER_Pin, GPIO_PIN_SET);
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

	Update_Aux_State(auxiliary, Toggle_State_Right, Toggle_State_Left);
	Can_Transmit_Auxiliary_Activity_Check(hcan);

  /* USER CODE END TIM3_IRQn 1 */
}

/*
 * Drives all auxiliary outputs based on the current state bitfield.
 * Outputs are active-low (P-channel MOSFETs), so GPIO is written inverted.
 */
void Update_Aux_State(aux_state *auxiliary,
                      bool Toggle_State_Right, bool Toggle_State_Left)
{
	/* Hazard lights: force both blinkers on and sync their timers */
	if (auxiliary->avarie == ON && Toggle_State_Left == Toggle_State_Right)
	{
		Sign_Right_500ms_Timer = Sign_Left_500ms_Timer;
		auxiliary->sign_left = ON;
		auxiliary->sign_right = ON;
	}

	/* Left blinker */
	if (auxiliary->sign_left == ON)
	{
		if (auxiliary->avarie == OFF)
			auxiliary->sign_right = OFF;
		if (++Sign_Left_500ms_Timer == 6)
		{
			HAL_GPIO_TogglePin(GPIOB, SIGN_LEFT_Pin);
			Sign_Left_500ms_Timer = 0;
			Toggle_State_Left = (!Toggle_State_Left);
		}
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, SIGN_LEFT_Pin, !(auxiliary->sign_left));
		Sign_Left_500ms_Timer = 0;
		Toggle_State_Left = OFF;
	}

	/* Right blinker */
	if (auxiliary->sign_right == ON)
	{
		if (auxiliary->avarie == OFF)
			auxiliary->sign_left = OFF;
		if (++Sign_Right_500ms_Timer == 6)
		{
			HAL_GPIO_TogglePin(GPIOB, SIGN_RIGHT_Pin);
			Sign_Right_500ms_Timer = 0;
			Toggle_State_Right = (!Toggle_State_Right);
		}
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, SIGN_RIGHT_Pin, !(auxiliary->sign_right));
		Sign_Right_500ms_Timer = 0;
		Toggle_State_Right = OFF;
	}

	/* Direct outputs (active-low) */
	HAL_GPIO_WritePin(GPIOC, HORN_Pin, (!auxiliary->horn));
	HAL_GPIO_WritePin(GPIOB, CAMERA_Pin, (!auxiliary->camera));
	HAL_GPIO_WritePin(GPIOB, /*BACK_LIGHT_Pin |*/ FRONT_LIGHT_Pin, (!auxiliary->faruri));
	HAL_GPIO_WritePin(GPIOB, BRAKE_Pin, (!auxiliary->brake));
	HAL_GPIO_WritePin(GPIOA, FAN_Pin, (!auxiliary->fan));
}

/* Reads physical switches to populate the auxiliary state in offline mode */
void Update_Buttons_State_Offline_Mode(aux_state *Offline_Mode)
{
	Offline_Mode->brake = HAL_GPIO_ReadPin(GPIOA, BRAKE_OFFLINE_MODE_Pin);
	Offline_Mode->camera = HAL_GPIO_ReadPin(GPIOB, CAMERA_OFFLINE_MODE_Pin);
	Offline_Mode->fan = HAL_GPIO_ReadPin(GPIOB, FAN_OFFLINE_MODE_Pin);
	Offline_Mode->horn = HAL_GPIO_ReadPin(GPIOB, HORN_OFFLINE_MODE_Pin);
	Offline_Mode->sign_left = HAL_GPIO_ReadPin(GPIOB, SIGN_LEFT_OFFLINE_MODE_Pin);
	Offline_Mode->sign_right = HAL_GPIO_ReadPin(GPIOB, SIGN_RIGHT_OFFLINE_MODE_Pin);

	/* Hazard: both left and right switches on simultaneously */
	if (HAL_GPIO_ReadPin(GPIOB, SIGN_LEFT_OFFLINE_MODE_Pin) && HAL_GPIO_ReadPin(GPIOB, SIGN_RIGHT_OFFLINE_MODE_Pin))
	{
		Offline_Mode->avarie = ON;
	}
	else
	{
		Offline_Mode->avarie = OFF;
	}

	/* Headlights: either front or back light switch enables */
	if (HAL_GPIO_ReadPin(GPIOB, FRONT_LIGHT_OFFLINE_MODE_Pin) || HAL_GPIO_ReadPin(GPIOB, BACK_LIGHT_OFFLINE_MODE_Pin))
	{
		Offline_Mode->faruri = ON;
	}
	else
	{
		Offline_Mode->faruri = OFF;
	}
}
