/* 
 * File:   ecu_relay.h
 * Author: anter
 *
 * Created on August 13, 2024, 3:48 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section : includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_relay_cfg.h"

/* Section : Macro Declarations*/

#define RELAY_ON_STATE 0X01U
#define RELAY_OFF_STATE 0x00U

/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/

typedef struct {
    uint8 relay_port   : 4;
    uint8 relay_pin    : 3;
    uint8 relay_status : 1;
}relay_t;

/* Section : Function Declarations*/

Std_ReturnType relay_initialize(const relay_t *relay);
Std_ReturnType relay_turn_on(const relay_t *relay);
Std_ReturnType relay_turn_off(const relay_t *relay);





#endif	/* ECU_RELAY_H */

