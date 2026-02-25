#include "main.h"

/* Heartbeat LED toggle, called from the main while(1) loop */
void loop()
{
	static uint8_t status = 0;

	HAL_GPIO_WritePin(GPIOA, HEARTH_BEAT_Pin, status);
	status = !status;
	HAL_Delay(500);
}
