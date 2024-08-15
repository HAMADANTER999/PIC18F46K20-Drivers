/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

pin_config_t seg1_enable = {
    .port =  PORTD_INDEX,
    .pin  = GPIO_PIN0,
    .logic = GPIO_LOW,
    .direction = GPIO_DIRECTION_OUTPUT,
};

pin_config_t seg2_enable = {
    .port =  PORTD_INDEX,
    .pin  = GPIO_PIN1,
    .logic = GPIO_LOW,
    .direction = GPIO_DIRECTION_OUTPUT,
};

segment_t seg1 = {
    .segments_pins[SEGMENT_PIN0].port = PORTC_INDEX,
    .segments_pins[SEGMENT_PIN0].pin  = GPIO_PIN0,
    .segments_pins[SEGMENT_PIN0].direction = GPIO_DIRECTION_OUTPUT,
    .segments_pins[SEGMENT_PIN0].logic = GPIO_LOW,
    .segments_pins[SEGMENT_PIN1].port = PORTC_INDEX,
    .segments_pins[SEGMENT_PIN1].pin  = GPIO_PIN1,
    .segments_pins[SEGMENT_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    .segments_pins[SEGMENT_PIN1].logic = GPIO_LOW,
    .segments_pins[SEGMENT_PIN2].port = PORTC_INDEX,
    .segments_pins[SEGMENT_PIN2].pin  = GPIO_PIN2,
    .segments_pins[SEGMENT_PIN2].direction = GPIO_DIRECTION_OUTPUT,
    .segments_pins[SEGMENT_PIN2].logic = GPIO_LOW,
    .segments_pins[SEGMENT_PIN3].port = PORTC_INDEX,
    .segments_pins[SEGMENT_PIN3].pin  = GPIO_PIN3,
    .segments_pins[SEGMENT_PIN3].direction = GPIO_DIRECTION_OUTPUT,
    .segments_pins[SEGMENT_PIN3].logic = GPIO_LOW,
    .segment_type = SEGMENT_COMMON_ANODE
};

Std_ReturnType ret = E_NOT_OK;
uint8 number = 90 , counter = 0;

int main() {
    Application ();
    
    while (1)
    {
        for (counter = 0 ; counter <= 50 ; counter++)
        {
            seven_segment_write_number(&seg1, ((uint8)number/10));
            gpio_pin_write_logic(&seg1_enable, GPIO_HIGH);
            __delay_ms(10);
            gpio_pin_write_logic(&seg1_enable, GPIO_LOW);
        
            seven_segment_write_number(&seg1, ((uint8)number%10));
            gpio_pin_write_logic(&seg2_enable, GPIO_HIGH);
            __delay_ms(10); 
            gpio_pin_write_logic(&seg2_enable, GPIO_LOW);
        }
        number++;
        if (number == 100)
        {
            number = 0;
        }
    }
    return (EXIT_SUCCESS);
}
void Application (void)
{
    ret = seven_segment_intialize(&seg1);
    ret = gpio_pin_intialize(&seg1_enable);
    ret = gpio_pin_intialize(&seg2_enable);
    
}

