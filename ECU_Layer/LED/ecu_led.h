/* 
 * File:   ecu_led.h
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/* Section : Macro Declarations*/

/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/
typedef enum{
    LED_OFF = 0,
    LED_ON,
}led_status;

typedef struct{
    uint8 port_name  : 4;
    uint8 pin        : 3;
    uint8 led_status : 1;
}led_t;

/* Section : Function Declarations*/

Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_turn_toggle(const led_t *led);



#endif	/* ECU_LED_H */

