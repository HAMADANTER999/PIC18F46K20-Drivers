/* 
 * File:   ecu_button.h
 * Author: anter
 *
 * Created on August 12, 2024, 12:15 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"

/* Section : Macro Declarations*/

/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/

typedef enum {
    BUTTON_PRESSED = 0,
    BUTTON_RELEASED
}button_state_t;

typedef enum {
    BUTTON_ACTIVE_HIGH = 0,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct {
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_conection;
}button_t;
/* Section : Function Declarations*/

Std_ReturnType button_initialize(const button_t *btn);
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);
    

#endif	/* ECU_BUTTON_H */

