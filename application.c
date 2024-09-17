/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"


void Application (void);
void Timer3_DefualtInterruptHandler(void);
timer3_t timer3_obj;
volatile uint16 counter_val;

Std_ReturnType ret = E_NOT_OK;
int main() {
    //Application ();
    timer3_obj.TMR3_InterruptHandler = NULL;
    timer3_obj.timer3_mode = TIMER3_COUNTER_MODE;
    timer3_obj.timer3_preloaded_value = 0;
    timer3_obj.timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_1;
    timer3_obj.timer3_reg_wr_mode = TIMER3_RW_REG_16BIT_MODE;
    timer3_obj.timer3_counter_mode = TIMER3_SYNC_COUNTER_MODE;
    Timer3_Init(&timer3_obj);

    while (1)
    {
       ret = Timer3_Read_Value(&timer3_obj, &counter_val);
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ecu_layer_initialize();
}


