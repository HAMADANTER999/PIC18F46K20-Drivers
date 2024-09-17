/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"


void Application (void);
volatile uint16 timer_counter;

timer2_t timer2_obj;
void Timer2_DefualtInterruptHandler(void){
    timer_counter++;
}






Std_ReturnType ret = E_NOT_OK;
int main() {
    //Application ();
    timer2_obj.TMR2_InterruptHandler = Timer2_DefualtInterruptHandler;
    timer2_obj.timer2_prescaler_value = TIMER2_PRESCALER_DIV_BY_1;
    timer2_obj.timer2_postscaler_value = TIMER2_POSTSCALER_DIV_BY_16;
    timer2_obj.timer2_preloaded_value = 249;
    ret = Timer2_Init(&timer2_obj);
    while (1)
    {
       
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ecu_layer_initialize();
}

