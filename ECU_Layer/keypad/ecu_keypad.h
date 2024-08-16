/* 
 * File:   ecu_keypad.h
 * Author: anter
 *
 * Created on August 16, 2024, 1:33 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : includes*/
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/* Section : Macro Declarations*/
#define ECU_KEYPAD_ROWS      4
#define ECU_KEYPAD_COLUMNS   4

/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/

typedef struct {
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
    
}keypad_t;
/* Section : Function Declarations*/
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);






#endif	/* ECU_KEYPAD_H */

