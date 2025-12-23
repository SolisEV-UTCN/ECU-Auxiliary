/*
 * mode.c
 *
 *  Created on: Dec 23, 2025
 *      Author: relu
 */



#include "main.h"

void mode(void){

	if(globals.dash_timeout > 10 || HAL_GPIO_ReadPin(OFFLINE_MODE_GPIO_Port, OFFLINE_MODE_GPIO_Port))
		globals.mode = OFF;	// no response from the dash for 5s or offline mode is manually set on
	else
		globals.mode = ON;

}

