/* 
 * File:   ecu_dc_motor.h
 * Author: anter
 *
 * Created on August 13, 2024, 10:27 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Section : includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_dc_motor_cfg.h"

/* Section : Macro Declarations*/
#define DC_MOTOR_ON_STATUS 0X01U
#define DC_MOTOR_OFF_STATUS 0X00U
/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/

typedef struct {
    uint8 dc_motor_port   : 4;
    uint8 dc_motor_pin    : 3;
    uint8 dc_motor_status : 1;
}dc_motor_pin_t;

typedef struct {
    dc_motor_pin_t dc_motor[2];
}dc_motor_t;

/* Section : Function Declarations*/

Std_ReturnType dc_motor_initialize(dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right(dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left(dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(dc_motor_t *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

