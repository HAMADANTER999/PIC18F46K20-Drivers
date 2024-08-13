/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

relay_t relay_1 = {
    .relay_pin = GPIO_PIN0,
    .relay_port = PORTC_INDEX,
    .relay_status = RELAY_OFF_STATE,
};

relay_t relay_2 = {
    .relay_pin = GPIO_PIN1,
    .relay_port = PORTC_INDEX,
    .relay_status = RELAY_OFF_STATE,
};

Std_ReturnType ret = E_NOT_OK;

int main() {
    Application ();
    
    while (1)
    {
        relay_turn_on(&relay_1);
        relay_turn_off(&relay_2);
        __delay_ms(5000);
        relay_turn_on(&relay_2);
        relay_turn_off(&relay_1);
        __delay_ms(5000);
    }
        
        
        
    
    
    return (EXIT_SUCCESS);
}
void Application (void)
{
    ret = relay_initialize(&relay_1);
    ret = relay_initialize(&relay_2);
}

