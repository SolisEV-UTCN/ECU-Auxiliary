/*
 * aux.h
 *
 *  Created on: Nov 18, 2025
 *      Author: relu
 */

#ifndef INC_AUX_H_
#define INC_AUX_H_

#define DASHBOARD_ID 0x701
#define AUXILIARY_ID 0x700

void mode(void);
void update(void);
void Can_Transmit_Auxiliary_Activity_Check(CAN_HandleTypeDef hcan);

typedef union {
	uint8_t state;
	struct {
		uint8_t sign_left :1; // 0x01
		uint8_t sign_right :1; // 0x02
		uint8_t fan :1; // 0x04
		uint8_t brake :1; // 0x08

		uint8_t horn :1; // 0x10
		uint8_t avarie :1; // 0x20
		uint8_t camera :1; // 0x30
		uint8_t faruri :1; // 0x80
	};
} aux_state;
extern aux_state state;

typedef enum
{
	OFF = 0,
	ON
}bool;

typedef struct {
	bool mode;
	uint8_t dash_timeout;
} sGlobals;
extern sGlobals globals;

#endif /* INC_AUX_H_ */
