/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

Std_ReturnType ret = E_NOT_OK;
uint8 keypad_value = ZERO_INIT;

int main() {
    Application ();
    while (1)
    {
        ret = keypad_get_value(&keypad1, &keypad_value);
        if (keypad_value == '1')
        {
            ret = led_turn_on(&led_1);
        }
        else if (keypad_value == '2')
        {
            ret = led_turn_off(&led_1);
        }
        else {}
            
            
        
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ecu_layer_initialize();
}

