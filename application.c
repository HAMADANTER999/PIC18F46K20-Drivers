/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

Std_ReturnType ret = E_NOT_OK;





uint8 lcd_counter = ZERO_INIT;
uint8 lcd_counter_txt[4];

int main() {
    Application ();
    ret = lcd_8bit_send_string_pos(&lcd_2, 2, 7, "loading   %");
    while (1)
    {
        ret = convert_byte_to_string(lcd_counter, lcd_counter_txt);
        ret = lcd_8bit_send_string_pos(&lcd_2, 2, 15, lcd_counter_txt);
        __delay_ms(50);
        if (lcd_counter == 100)
        {
            ret = lcd_8bit_send_string_pos(&lcd_2, 2, 5, "Done successful");
            exit(1);
        }
        else {
            lcd_counter++;
        }
   
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ecu_layer_initialize();
}




