#include"main.h"

//this is the main loop
void loop() {
	// we are flipping the hearthbeat led every 500ms
	static uint8_t status = 0;
	HAL_GPIO_WritePin(GPIOA, HEARTH_BEAT_Pin, status);
	status = !status;
	HAL_Delay(500);
}
