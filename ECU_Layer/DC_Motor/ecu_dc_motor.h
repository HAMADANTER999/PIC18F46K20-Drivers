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
#define DC_MOTOR_ON_STATUS  0X01U
#define DC_MOTOR_OFF_STATUS 0X00U

#define MOTOR_INDEX_PIN1    0X00U
#define MOTOR_INDEX_PIN2    0X01U

#define MOTOR_PINS          0x02U

/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/

typedef struct {
    pin_config_t dc_motor[MOTOR_PINS];
}dc_motor_t;

/* Section : Function Declarations*/

Std_ReturnType dc_motor_initialize(dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right(dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left(dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(dc_motor_t *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

