/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

void program_1(void);
void program_2(void);
void APP_CallBack(void);

Std_ReturnType ret = E_NOT_OK;
led_t led_1 = {
    .led_status = LED_OFF,
    .pin = GPIO_PIN0,
    .port_name = PORTD_INDEX,
};

led_t led_2 = {
    .led_status = LED_OFF,
    .pin = GPIO_PIN1,
    .port_name = PORTD_INDEX,
};


interrupt_INTx_t int0_obj = {
    .EXT_InterruptHandler = APP_CallBack,
    .edge = INTERRUPT_RISING_EDGE,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.port = PORTB_INDEX,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT0,
};

volatile uint8 program_selected = ZERO_INIT;
int main() {

    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    
    ret = Interrupt_INTx_Init(&int0_obj);
    ret = Data_EEPROM_ReadByte(0x3E0, &program_selected);
    
    while (1)
    {
        if (1 == program_selected)
        {
            program_1();
        }
        else if (2 == program_selected)
        {
            program_2();
        }
        else{
            led_turn_off(&led_1);
            led_turn_off(&led_2);
        }
            
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ecu_layer_initialize();
}

void program_1(void){
    led_turn_on(&led_1);
    __delay_ms(250);
    led_turn_off(&led_1);
    __delay_ms(250);
}

void program_2(void){
    led_turn_on(&led_2);
    __delay_ms(250);
    led_turn_off(&led_2);
    __delay_ms(250);
}

void APP_CallBack(void){
    program_selected++;
    if (3 == program_selected)
    {
        program_selected = 0;
    }
    else{}
    ret = Data_EEPROM_WriteByte(0x3E0, program_selected);
}




