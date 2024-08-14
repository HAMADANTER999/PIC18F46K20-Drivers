/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

dc_motor_t dc_motor_1 = {
    .dc_motor[MOTOR_INDEX_PIN1].port = PORTC_INDEX,
    .dc_motor[MOTOR_INDEX_PIN1].pin = GPIO_PIN0,
    .dc_motor[MOTOR_INDEX_PIN1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[MOTOR_INDEX_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[MOTOR_INDEX_PIN2].port = PORTC_INDEX,
    .dc_motor[MOTOR_INDEX_PIN2].pin = GPIO_PIN1,
    .dc_motor[MOTOR_INDEX_PIN2].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[MOTOR_INDEX_PIN2].direction = GPIO_DIRECTION_OUTPUT,
};

dc_motor_t dc_motor_2 = {
    .dc_motor[MOTOR_INDEX_PIN1].port = PORTC_INDEX,
    .dc_motor[MOTOR_INDEX_PIN1].pin = GPIO_PIN2,
    .dc_motor[MOTOR_INDEX_PIN1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[MOTOR_INDEX_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[MOTOR_INDEX_PIN2].port = PORTC_INDEX,
    .dc_motor[MOTOR_INDEX_PIN2].pin = GPIO_PIN3,
    .dc_motor[MOTOR_INDEX_PIN2].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[MOTOR_INDEX_PIN2].direction = GPIO_DIRECTION_OUTPUT,
};


Std_ReturnType ret = E_NOT_OK;

int main() {
    Application ();
    
    while (1)
    {
        ret = dc_motor_move_right(&dc_motor_1);
        ret = dc_motor_move_right(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_left(&dc_motor_1);
        ret = dc_motor_move_left(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_stop(&dc_motor_1);
        ret = dc_motor_stop(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_right(&dc_motor_1);
        ret = dc_motor_move_left(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_stop(&dc_motor_1);
        ret = dc_motor_stop(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_left(&dc_motor_1);
        ret = dc_motor_move_right(&dc_motor_2);
        __delay_ms(3000);
    }
        
        
        
    
    
    return (EXIT_SUCCESS);
}
void Application (void)
{
    ret = dc_motor_initialize(&dc_motor_1);
    ret = dc_motor_initialize(&dc_motor_2);
}

