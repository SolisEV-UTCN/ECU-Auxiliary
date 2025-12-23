/*
 * update.c
 *
 *  Created on: Dec 23, 2025
 *      Author: relu
 */



#include "main.h"

// every output is enabled on low so that's why everything is flipped
void update() {
	aux_state temp_state;
	// offline mode
	if (!globals.mode) {
		temp_state.brake = HAL_GPIO_ReadPin(OFFLINE_BRAKE_GPIO_Port,
		OFFLINE_BRAKE_Pin);
		temp_state.camera = HAL_GPIO_ReadPin(OFFLINE_CAMERA_GPIO_Port,
		OFFLINE_CAMERA_Pin);
		temp_state.fan = HAL_GPIO_ReadPin(OFFLINE_FAN_GPIO_Port,
		OFFLINE_FAN_Pin);
		temp_state.horn = HAL_GPIO_ReadPin(OFFLINE_HORN_GPIO_Port,
		OFFLINE_HORN_Pin);
		temp_state.sign_left = HAL_GPIO_ReadPin(OFFLINE_SIGNAL_LEFT_GPIO_Port,
		OFFLINE_SIGNAL_LEFT_Pin);
		temp_state.sign_right = HAL_GPIO_ReadPin(OFFLINE_SIGNAL_RIGHT_GPIO_Port,
		OFFLINE_SIGNAL_RIGHT_Pin);
		if (temp_state.sign_left && temp_state.sign_right)
			temp_state.avarie = ON;

		// why are the headlights turning on if the brake light is on?
		// i'll just leave it as is and ask later
		if (HAL_GPIO_ReadPin(OFFLINE_FRONT_LIGHT_GPIO_Port,
				OFFLINE_FRONT_LIGHT_Pin)
				|| HAL_GPIO_ReadPin(OFFLINE_BACK_LIGHT_GPIO_Port,
						OFFLINE_BACK_LIGHT_Pin))
			temp_state.faruri = ON;
		else
			temp_state.faruri = OFF;
	} else { // online mode
		temp_state = state; // we are setting the state we recieved from the dash
	}

	static uint8_t blinker_counter;

	// handles signals
	// if it needs to be synced when switching from signal to hazzards i will do it
	if (temp_state.avarie) {
		// toggle every 500ms
		if (blinker_counter < 10) {
			HAL_GPIO_WritePin(SIGNAL_LEFT_GPIO_Port, SIGNAL_LEFT_Pin, OFF);
			HAL_GPIO_WritePin(SIGNAL_RIGHT_GPIO_Port, SIGNAL_RIGHT_Pin, OFF);
		} else {
			HAL_GPIO_WritePin(SIGNAL_LEFT_GPIO_Port, SIGNAL_LEFT_Pin, ON);
			HAL_GPIO_WritePin(SIGNAL_RIGHT_GPIO_Port, SIGNAL_RIGHT_Pin, ON);
		}
		if (++blinker_counter == 20)
			blinker_counter = 0;
	} else if (temp_state.sign_left) { // only signal left
		// toggle every 500ms
		if (blinker_counter < 10) {
			HAL_GPIO_WritePin(SIGNAL_LEFT_GPIO_Port, SIGNAL_LEFT_Pin, OFF);
		} else {
			HAL_GPIO_WritePin(SIGNAL_LEFT_GPIO_Port, SIGNAL_LEFT_Pin, ON);
		}
		if (++blinker_counter == 20)
			blinker_counter = 0;

	} else if (temp_state.sign_right) { // only signal right
		// toggle every 500ms
		if (blinker_counter < 10) {
			HAL_GPIO_WritePin(SIGNAL_RIGHT_GPIO_Port, SIGNAL_RIGHT_Pin, OFF);
		} else {
			HAL_GPIO_WritePin(SIGNAL_RIGHT_GPIO_Port, SIGNAL_RIGHT_Pin, ON);
		}
		if (++blinker_counter == 20)
			blinker_counter = 0;

	} else { // no hazzards no signal
		HAL_GPIO_WritePin(SIGNAL_LEFT_GPIO_Port, SIGNAL_LEFT_Pin, ON);
		HAL_GPIO_WritePin(SIGNAL_RIGHT_GPIO_Port, SIGNAL_RIGHT_Pin, ON);
		blinker_counter = 0;
	}

	HAL_GPIO_WritePin(HORN_GPIO_Port, HORN_Pin, (!temp_state.horn));
	HAL_GPIO_WritePin(CAMERA_GPIO_Port, CAMERA_Pin, (!temp_state.camera));
	HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, (!temp_state.fan));
	HAL_GPIO_WritePin(BRAKE_GPIO_Port, BRAKE_Pin, (!temp_state.brake));
	HAL_GPIO_WritePin(FRONT_LIGHT_GPIO_Port, FRONT_LIGHT_Pin, (!temp_state.faruri));
}
