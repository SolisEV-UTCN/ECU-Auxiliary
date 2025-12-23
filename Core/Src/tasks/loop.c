/*
 * loop.c
 *
 *  Created on: Dec 23, 2025
 *      Author: relu
 */


#include "main.h"

sGlobals globals;
aux_state state;

// this is the "main loop" of the code
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) // every 10ms
{
	static uint32_t ticks = 0;
	static uint32_t loops = 0;

	// we are flipping the hearthbeat led every 500ms
	// also we could write directly to the registers to save 2 cycles but it's not needed i guess
	HAL_GPIO_WritePin(HEARTHBEAT_GPIO_Port, HEARTHBEAT_Pin, (ticks >= 50));

	// we are calling mode every 5 ticks (50ms)
	if (!(ticks % 5))
		mode(); // handles offline/online mode switching

	// we are calling update every 5 ticks (50ms)
	if (!(ticks % 5))
		update(); // updates state(offline), handles logic and outputs to pins

	if (htim->Instance == TIM2) {
		if(++ticks == 100){
			ticks = 0;
			loops++;
		}
		if(loops == 2)
			HAL_GPIO_WritePin(ENABLE_POWER_GPIO_Port, ENABLE_POWER_Pin, ON);
	}
}

