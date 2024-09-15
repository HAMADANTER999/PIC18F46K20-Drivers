/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

void Application (void);
void TMR_DefaultInterruptHandler(void);

volatile uint16 counter_flag = ZERO_INIT;

timer0_t timer0_timer_obj = {
  .TMR0_InterruptHandler = TMR_DefaultInterruptHandler,
  .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
  .prescaler_value = TIMER0_PRESCALER_DIV_BY_8,
  .timer0_mode = TIMER0_TIMER_MODE,
  .timer0_register_size = TIMER0_16BIT_REGOSTER_MODE,
  .timer0_preloaded_value = 3036,
  
};

timer0_t timer0_counter_obj = {
  .TMR0_InterruptHandler = TMR_DefaultInterruptHandler,
  .prescaler_enable = TIMER0_PRESCALER_DISABLE_CFG,
  .timer0_mode = TIMER0_COUNTER_MODE,
  .timer0_register_size = TIMER0_16BIT_REGOSTER_MODE,
  .timer0_counter_edge = TIMER0_RISING_EDGE_CFG,
  .timer0_preloaded_value = 0,
  
};

led_t led_1 = {
  .led_status = LED_OFF,
  .pin = GPIO_PIN0,
  .port_name = PORTD_INDEX,
};
Std_ReturnType ret = E_NOT_OK;
int main() {
    Application ();

    while (1)
    {
        ret = Timer0_Read_Value(&timer0_counter_obj, &counter_flag);
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ret = Timer0_Init(&timer0_counter_obj);
    ret = led_initialize(&led_1);
    ecu_layer_initialize();
}

void TMR_DefaultInterruptHandler(void){
    ret = led_turn_toggle(&led_1);
}
