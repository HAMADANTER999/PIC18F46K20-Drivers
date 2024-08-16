/* 
 * File:   ecu_layer_init.c
 * Author: anter
 *
 * Created on August 16, 2024, 4:41 PM
 */

#include "ecu_layer_init.h"

Std_ReturnType ret = E_NOT_OK;

keypad_t keypad1 = {
    .keypad_row_pins[0].port = PORTC_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[0].logic = GPIO_LOW,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].port = PORTC_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[1].logic = GPIO_LOW,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].port = PORTC_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[2].logic = GPIO_LOW,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].port = PORTC_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN3,
    .keypad_row_pins[3].logic = GPIO_LOW,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_columns_pins[0].port = PORTC_INDEX,
    .keypad_columns_pins[0].pin = GPIO_PIN4,
    .keypad_columns_pins[0].logic = GPIO_LOW,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].port = PORTC_INDEX,
    .keypad_columns_pins[1].pin = GPIO_PIN5,
    .keypad_columns_pins[1].logic = GPIO_LOW,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].port = PORTC_INDEX,
    .keypad_columns_pins[2].pin = GPIO_PIN6,
    .keypad_columns_pins[2].logic = GPIO_LOW,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[3].port = PORTC_INDEX,
    .keypad_columns_pins[3].pin = GPIO_PIN7,
    .keypad_columns_pins[3].logic = GPIO_LOW,
    .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
};

led_t led_1 = {
    .port_name = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .led_status = LED_OFF
};

void ecu_layer_initialize (void)
{
    ret =  keypad_initialize(&keypad1);
    ret = led_initialize(&led_1);
}
