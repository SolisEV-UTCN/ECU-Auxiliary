#include"main.h"

void loop()
{
	 static uint8_t status = 0;

	 HAL_GPIO_WritePin(GPIOA, HEARTH_BEAT_Pin, status);
	 status = !status;
	 HAL_Delay(500);
}
