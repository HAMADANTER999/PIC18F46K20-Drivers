/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

void Application (void);
volatile uint16 timer_on = ZERO_INIT;
volatile uint16 counter_value = ZERO_INIT;

timer1_t counter_obj;
void Timer1_DefualtInterruptHandler(void){
    
}

void timer1_timer_init(void){
    timer1_t timer_obj; 
    timer_obj.TMR1_InterruptHandler = Timer1_DefualtInterruptHandler;
    timer_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer_obj.timer1_mode = TIMER1_TIMER_MODE;
    timer_obj.timer1_preloaded_value = 15536;
    timer_obj.timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_4;
    timer_obj.timer1_reg_wr_mode = TIMER1_RW_REG_16BIT_MODE;
    Timer1_Init(&timer_obj);
}



led_t led_1 = {
    .led_status = LED_OFF,
    .pin = GPIO_PIN0,
    .port_name = PORTD_INDEX,
};

Std_ReturnType ret = E_NOT_OK;
int main() {
    //Application ();
    //timer1_timer_init();
    
    counter_obj.TMR1_InterruptHandler = NULL;
    counter_obj.priority = INTERRUPT_LOW_PRIORITY;
    counter_obj.timer1_mode = TIMER1_COUNTER_MODE;
    counter_obj.timer1_preloaded_value = 0;
    counter_obj.timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_1;
    counter_obj.timer1_reg_wr_mode = TIMER1_RW_REG_16BIT_MODE;
    counter_obj.timer1_counter_mode = TIMER1_SYNC_COUNTER_MODE;
    Timer1_Init(&counter_obj);
    ret = led_initialize(&led_1);
    while (1)
    {
        ret = Timer1_Read_Value(&counter_obj, &timer_on);
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ecu_layer_initialize();
}

