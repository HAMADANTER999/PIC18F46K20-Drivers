/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

led_t led_1 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW,
};

led_t led_2 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_LOW,
};

led_t led_3 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .led_status = GPIO_LOW,
};

led_t led_4 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN3,
    .led_status = GPIO_LOW,
};

int main() {
    Application ();
    
    while (1)
    {
        /*
        led_turn_on(&led_1);
        led_turn_on(&led_2);
        led_turn_on(&led_3);
        led_turn_on(&led_4);
        __delay_ms(250);
        led_turn_off(&led_1);
        led_turn_off(&led_2);
        led_turn_off(&led_3);
        led_turn_off(&led_4);
        __delay_ms(250);
        */
        led_turn_toggle(&led_1);
        led_turn_toggle(&led_2);
        led_turn_toggle(&led_3);
        led_turn_toggle(&led_4);
        __delay_ms(100);

        
    }
    
    return (EXIT_SUCCESS);
}

void Application (void)
{
    Std_ReturnType ret = E_OK;
    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    ret = led_initialize(&led_3);
    ret = led_initialize(&led_4);
    
}


