/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

Std_ReturnType ret = E_NOT_OK;
led_t led_1 = {
    .led_status = LED_OFF,
    .pin = GPIO_PIN0,
    .port_name = PORTD_INDEX,
};

uint8 eeprom_val = ZERO_INIT;
uint8 eeprom_val_read = ZERO_INIT;

int main() {

    ret = led_initialize(&led_1);
    ret = Data_EEPROM_WriteByte(0x3FF, 0);
    
    while (1)
    {
        ret = Data_EEPROM_WriteByte(0x3FF, eeprom_val++);
        __delay_ms(1000);
        ret = Data_EEPROM_ReadByte(0x3FF, &eeprom_val_read);
        
        if (5 == eeprom_val_read)
        {
            ret = led_turn_on(&led_1);
        } 
        else 
        {
            ret = led_turn_off(&led_1);
        }
        
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ecu_layer_initialize();
}


