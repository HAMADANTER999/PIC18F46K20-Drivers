/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

button_t btn_high = {
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_pin.pin = GPIO_PIN2,
    .button_pin.port = PORTC_INDEX,
    .button_conection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED,
};

button_t btn_low = {
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_HIGH,
    .button_pin.pin = GPIO_PIN0,
    .button_pin.port = PORTD_INDEX,
    .button_conection = BUTTON_ACTIVE_LOW,
    .button_state = BUTTON_RELEASED,
};

led_t led_1 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = LED_OFF,
};

led_t led_2 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = LED_OFF,
};
void program_1(void);
void program_2(void);
void program_3(void);

button_state_t btn_high_status = BUTTON_RELEASED;
button_state_t btn_low_status = BUTTON_RELEASED;
button_state_t btn_high_valid_status = BUTTON_RELEASED;
button_state_t btn_high_last_valid_status = BUTTON_RELEASED;
led_status led1_status = LED_OFF;

Std_ReturnType ret = E_OK;
uint32 btn_high_vaild = 0;
uint8 program_selected = 0;

int main() {
    Application ();
    
    while (1)
    {
        ret = button_read_state(&btn_high, &btn_high_status);
        if (btn_high_status == BUTTON_PRESSED)
        {
            btn_high_vaild++;
            if (btn_high_vaild > 500)
            {
                btn_high_valid_status = BUTTON_PRESSED;
            }
        }
        else
        {
            btn_high_vaild = 0;
            btn_high_valid_status = BUTTON_RELEASED;
        }
        
        if (btn_high_valid_status != btn_high_last_valid_status)
        {
            btn_high_last_valid_status = btn_high_valid_status;
            if (btn_high_valid_status == BUTTON_PRESSED)
            {
                if (3 == program_selected)
                {
                    program_selected = 0;
                }
                program_selected++;
                switch (program_selected)
                {
                    case 1  : program_1(); break;
                    case 2  : program_2(); break;
                    case 3  : program_3(); break;
                    default : /* Nothing */ break;
                }
            }
            
        }
        
        
        
        
    }
    
    return (EXIT_SUCCESS);
}

void Application (void)
{
    Std_ReturnType ret = E_OK;
    ret = button_initialize(&btn_high);
    //ret = button_initialize(&btn_low);
    ret = led_initialize(&led_1);
    //ret = led_initialize(&led_2);
}
void program_1(void)
{
    led_turn_on(&led_1);
    __delay_ms(100);
    led_turn_off(&led_1);
    __delay_ms(100);
    
    
} 

void program_2(void)
{
    uint8 counter = 0;
    for (counter = 0 ; counter < 2 ; counter++)
    {
        led_turn_on(&led_1);
        __delay_ms(100);
        led_turn_off(&led_1);
        __delay_ms(100);
    }
    
} 

void program_3(void)
{
    uint8 counter = 0;
    for (counter = 0 ; counter < 3 ; counter++)
    {
        led_turn_on(&led_1);
        __delay_ms(100);
        led_turn_off(&led_1);
        __delay_ms(100);
    }
    
} 


