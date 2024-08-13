/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

dc_motor_t dc_motor_1 = {
    .dc_motor[0].dc_motor_port = PORTC_INDEX,
    .dc_motor[0].dc_motor_pin = GPIO_PIN0,
    .dc_motor[0].dc_motor_status = DC_MOTOR_OFF_STATUS,
    .dc_motor[1].dc_motor_port = PORTC_INDEX,
    .dc_motor[1].dc_motor_pin = GPIO_PIN1,
    .dc_motor[1].dc_motor_status = DC_MOTOR_OFF_STATUS,
};


Std_ReturnType ret = E_NOT_OK;

int main() {
    Application ();
    
    while (1)
    {
        
    }
        
        
        
    
    
    return (EXIT_SUCCESS);
}
void Application (void)
{
    
}

