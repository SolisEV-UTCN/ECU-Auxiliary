#include"main.h"

extern CAN_HandleTypeDef hcan;

//sending back every 50ms an alive signal back to the dash
void Can_Transmit_Auxiliary_Activity_Check(CAN_HandleTypeDef hcan) {

	static const CAN_TxHeaderTypeDef TxHeader = { AUXILIARY_ID, 0x00,
		CAN_RTR_DATA, CAN_ID_STD, 1, DISABLE };

		static uint32_t TxMailBox;

		HAL_CAN_AddTxMessage(&hcan, &TxHeader, 0x00, &TxMailBox);
}
