/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

pin_config_t led_1 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

pin_config_t led_2 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

pin_config_t led_3 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

pin_config_t btn_1 = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIRECTION_INPUT,
    .logic = GPIO_LOW
};

Std_ReturnType ret = E_OK;
direction_t led_1_st;
logic_t btn1_status;

uint8 portc_direction_status, portc_logic_status;


int main() {
    Application ();
    
    while (1)
    {
        gpio_port_toggle_logic(PORTC_INDEX);
        __delay_ms(10);
        
        
    }
    
    
    

    return (EXIT_SUCCESS);
}

void Application (void)
{
    /*
    ret = gpio_pin_intialize(&btn_1);
    
    ret = gpio_pin_intialize(&led_1);
    ret = gpio_pin_intialize(&led_2);
    ret = gpio_pin_intialize(&led_3);
    */
    ret = gpio_port_direction_intialize(PORTC_INDEX, 0x00);
    ret = gpio_port_get_direction_status(PORTC_INDEX, &portc_direction_status);
    ret = gpio_port_write_logic(PORTC_INDEX, 0xAA);
    
    //ret = gpio_port_read_logic(PORTC_INDEX, &portc_logic_status);
    //ret = gpio_port_read_logic(PORTC_INDEX, &portc_logic_status);
}


