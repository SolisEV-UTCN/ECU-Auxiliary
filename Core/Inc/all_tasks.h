#ifndef INC_ALL_TASKS_H_
#define INC_ALL_TASKS_H_

#include "main.h"
#include "stm32f3xx_hal.h"
//#include "stm32f3xx_hal_can.h"

#define DASHBOARD_ID 0x701
#define AUXILIARY_ID 0x700
#define SAFE_STATE 0x00

#define AUXILIARY_WORKS 0xFF
#define AUXILIARY_ERROR 0x00

typedef union
{
    uint8_t state;
    struct
    {
        uint8_t sign_left  : 1; // 0x01
        uint8_t sign_right : 1; // 0x02
        uint8_t fan        : 1; // 0x04
        uint8_t brake      : 1; // 0x08

        uint8_t horn       : 1; // 0x10
        uint8_t avarie     : 1; // 0x20
        uint8_t camera     : 1; // 0x30
        uint8_t faruri     : 1; // 0x80
    };
} aux_state;

typedef struct
{
    uint32_t Sign_Left_Current;
    uint32_t Sign_Right_Current;
    uint32_t Fan_Current;
    uint32_t Brake_Current;
    uint32_t Horn_Current;
    uint32_t Avarie_Current;
    uint32_t Camera_Current;
    uint32_t Faruri_Current;
} Aux_Error;

typedef enum
{
    OFF = 0,
    ON
} bool;

void Update_Aux_State(aux_state* auxiliary, bool Toggle_State_Right, bool Toggle_State_Left);

void Update_Buttons_State_Offline_Mode(aux_state* Offline_Mode);

void Can_Transmit_Auxiliary_Activity_Check(CAN_HandleTypeDef hcan);

#endif /* INC_ALL_TASKS_H_ */

