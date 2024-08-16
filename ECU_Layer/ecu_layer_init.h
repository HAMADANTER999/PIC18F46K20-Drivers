/* 
 * File:   ecu_layer_init.h
 * Author: anter
 *
 * Created on August 16, 2024, 4:41 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H


/* Section : includes*/

#include <stdio.h>
#include <stdlib.h>
#include "LED/ecu_led.h"
#include "Button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "7_segment/ecu_seven_seg.h"
#include "keypad/ecu_keypad.h"

/* Section : Macro Declarations*/

/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/
extern keypad_t keypad1;
extern led_t led_1;

/* Section : Function Declarations*/
void ecu_layer_initialize (void);
#endif	/* ECU_LAYER_INIT_H */

