/* 
 * File:   ecu_layer_init.h
 * Author: anter
 *
 * Created on August 16, 2024, 4:41 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H


/* Section : includes*/

#include "LED/ecu_led.h"
#include "Button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "7_segment/ecu_seven_seg.h"
#include "keypad/ecu_keypad.h"
#include "chr_lcd/ecu_chr_lcd.h"

/* Section : Macro Declarations*/

/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/
extern chr_lcd_4bit_t lcd_1;
extern chr_lcd_8bit_t lcd_2;

/* Section : Function Declarations*/
void ecu_layer_initialize (void);
#endif	/* ECU_LAYER_INIT_H */

