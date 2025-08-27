#include"main.h"

extern CAN_HandleTypeDef hcan;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

//Signal left and right SWITCH STATE
bool Toggle_State_Right = OFF;
bool Toggle_State_Left = OFF;
bool Offline_Mode_Switch = OFF;

uint8_t Sign_Left_500ms_Timer = 0; // numaram pana la 10 ca sa avem 500ms intre toggle, STANDARD SEMNALIZARI
uint8_t Sign_Right_500ms_Timer = 0;
uint8_t Dash_Activity = 0;

aux_state Offline = {.state = 0x00};
aux_state* Offline_Mode = &Offline;

//auxiliary state variables when in NORMAL MODE OR OFFLINE MODE
aux_state aux = {.state = 0x00};
aux_state* auxiliary = &aux;


void TIM2_IRQHandler(void) // 56 ms
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

    //Check if Offline mode switch is ON/OFF
    	  Offline_Mode_Switch = HAL_GPIO_ReadPin(GPIOA, ENABLE_OFFLINE_MODE_Pin);

    //Dashboard CAN works
    	  if(Dash_Activity <= 100 && Offline_Mode_Switch == OFF) // 5.6 secunde daca nu se trimite niciun semnal de CAN
    	   {
    		  Dash_Activity++;
    	   }

  /* USER CODE END TIM2_IRQn 1 */
}

static uint8_t timer;
void TIM3_IRQHandler(void) //76 ms
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
	if(++timer == 26) // 2 seconds
		  HAL_GPIO_WritePin(GPIOB, ENABLE_POWER_Pin, GPIO_PIN_SET);
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  //Update auxiliary state based on TIM3 logic
    	  Update_Aux_State( auxiliary , Toggle_State_Right , Toggle_State_Left);

  //Transmit Activity Check CAN frame
    	  Can_Transmit_Auxiliary_Activity_Check( hcan );

  /* USER CODE END TIM3_IRQn 1 */
}

void Update_Aux_State( aux_state* auxiliary ,
					   bool Toggle_State_Right , bool Toggle_State_Left)
{
	//iesire sunt negate - Tranzistori tip P
		//avarie
		if( auxiliary->avarie == ON && Toggle_State_Left == Toggle_State_Right )
			{
				Sign_Right_500ms_Timer = Sign_Left_500ms_Timer; //sincronizare semnalizari
				auxiliary->sign_left = ON;
				auxiliary->sign_right = ON;
			}

		//semnalizare stanga
		if( auxiliary->sign_left == ON)
		{
			if( auxiliary->avarie == OFF ) auxiliary->sign_right = OFF;
			if(++Sign_Left_500ms_Timer == 6)
			{
				HAL_GPIO_TogglePin(GPIOB, SIGN_LEFT_Pin);
				Sign_Left_500ms_Timer = 0;
				Toggle_State_Left = (!Toggle_State_Left);
			}
		}
		else
			{
				//oprire semnalizare
				HAL_GPIO_WritePin(GPIOB, SIGN_LEFT_Pin, !(auxiliary->sign_left) );
				Sign_Left_500ms_Timer = 0;
				Toggle_State_Left = OFF;
			}

		//semanlizare dreapta
		if( auxiliary->sign_right == ON)
		{
			if( auxiliary->avarie == OFF) auxiliary->sign_left = OFF;
			if(++Sign_Right_500ms_Timer == 6)
			{
				HAL_GPIO_TogglePin(GPIOB, SIGN_RIGHT_Pin);
				Sign_Right_500ms_Timer = 0;
				Toggle_State_Right = (!Toggle_State_Right);
			}
		}
		else
			{
				//oprire semnalizare
				HAL_GPIO_WritePin(GPIOB, SIGN_RIGHT_Pin, !(auxiliary->sign_right) );
				Sign_Right_500ms_Timer = 0;
				Toggle_State_Right = OFF;
			}

		HAL_GPIO_WritePin(GPIOC, HORN_Pin, (!auxiliary->horn) );
		HAL_GPIO_WritePin(GPIOB, CAMERA_Pin, (!auxiliary->camera) );
		HAL_GPIO_WritePin(GPIOB, /*BACK_LIGHT_Pin |*/ FRONT_LIGHT_Pin, (!auxiliary->faruri) );
		HAL_GPIO_WritePin(GPIOB, BRAKE_Pin, (!auxiliary->brake) );
		HAL_GPIO_WritePin(GPIOA, FAN_Pin, (!auxiliary->fan) );

}

void Update_Buttons_State_Offline_Mode(aux_state* Offline_Mode)
{
	Offline_Mode->brake = HAL_GPIO_ReadPin(GPIOA, BRAKE_OFFLINE_MODE_Pin);
	Offline_Mode->camera = HAL_GPIO_ReadPin(GPIOB, CAMERA_OFFLINE_MODE_Pin);
	Offline_Mode->fan = HAL_GPIO_ReadPin(GPIOB, FAN_OFFLINE_MODE_Pin);
	Offline_Mode->horn = HAL_GPIO_ReadPin(GPIOB, HORN_OFFLINE_MODE_Pin);
	Offline_Mode->sign_left = HAL_GPIO_ReadPin(GPIOB, SIGN_LEFT_OFFLINE_MODE_Pin);
	Offline_Mode->sign_right = HAL_GPIO_ReadPin(GPIOB, SIGN_RIGHT_OFFLINE_MODE_Pin);

	//avarie
	if( HAL_GPIO_ReadPin(GPIOB, SIGN_LEFT_OFFLINE_MODE_Pin) && HAL_GPIO_ReadPin(GPIOB, SIGN_RIGHT_OFFLINE_MODE_Pin) )
	{
		Offline_Mode->avarie = ON;
	}
	else Offline_Mode->avarie = OFF;

	//faruri fata si spate
	if( HAL_GPIO_ReadPin(GPIOB, FRONT_LIGHT_OFFLINE_MODE_Pin) || HAL_GPIO_ReadPin(GPIOB, BACK_LIGHT_OFFLINE_MODE_Pin) )
	{
		Offline_Mode->faruri = ON;
	}
	else Offline_Mode->faruri = OFF;
}

