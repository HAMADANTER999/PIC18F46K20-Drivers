/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"




Std_ReturnType ret = E_NOT_OK;

uint8 seconds = 50, minutes = 59 , hours = 12;
uint8 counter = 0;
int main() {
    Application ();
    
    while (1)
    {
        for (counter = 0; counter <50; counter++)
        {
  
            ret = gpio_port_write_logic(PORTD_INDEX, 0x3E);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)(hours/10)));
            __delay_us(3333);
            ret = gpio_port_write_logic(PORTD_INDEX, 0x3D);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)(hours%10)));
            __delay_us(3333);
            ret = gpio_port_write_logic(PORTD_INDEX, 0x3B);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)(minutes/10)));
            __delay_us(3333);
            ret = gpio_port_write_logic(PORTD_INDEX, 0x37);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)(minutes%10)));
            __delay_us(3333);
            ret = gpio_port_write_logic(PORTD_INDEX, 0x2F);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)(seconds/10)));
            __delay_us(3333);
            ret = gpio_port_write_logic(PORTD_INDEX, 0x1F);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8)(seconds%10)));
            __delay_us(3333);
        }
        seconds++;
        if (seconds == 60)
        {
            minutes++;
            seconds = 0;
        }
        if (minutes == 60)
        {
            hours++;
            minutes = 0;
        }
        if (hours == 13)
        {
            hours = 1;
        }
        
       
    }
    return (EXIT_SUCCESS);
}
void Application (void)
{
    ret = gpio_port_direction_intialize(PORTC_INDEX, 0xF0);
    ret = gpio_port_direction_intialize(PORTD_INDEX, 0xC0);
    
}

