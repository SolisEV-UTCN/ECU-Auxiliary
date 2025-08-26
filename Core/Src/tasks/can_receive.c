#include"main.h"

extern CAN_HandleTypeDef hcan;
extern aux_state* auxiliary;

extern bool Offline_Mode_Switch;
extern uint8_t Dash_Activity;

void USB_LP_CAN_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN USB_LP_CAN_RX0_IRQn 0 */

	static CAN_RxHeaderTypeDef Rx_Dash_Header;
	static uint8_t Rx_Dash_Data[1];

  /* USER CODE END USB_LP_CAN_RX0_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan);
  /* USER CODE BEGIN USB_LP_CAN_RX0_IRQn 1 */

  //Get CAN message
  	  HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &Rx_Dash_Header, Rx_Dash_Data);

  //Get CAN message only if Offline Mode Switch is OFF
  		  auxiliary->state = Rx_Dash_Data[0];
  		  Dash_Activity = 0;

  /* USER CODE END USB_LP_CAN_RX0_IRQn 1 */
}
