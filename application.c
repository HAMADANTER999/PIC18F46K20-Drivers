/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

Std_ReturnType ret = E_NOT_OK;

void RB4_Int_APP_ISR_HIGH(void);
void RB4_Int_APP_ISR_LOW(void);
void RB5_Int_APP_ISR_HIGH(void);
void RB5_Int_APP_ISR_LOW(void);
void RB6_Int_APP_ISR_HIGH(void);
void RB6_Int_APP_ISR_LOW(void);
void RB7_Int_APP_ISR_HIGH(void);
void RB7_Int_APP_ISR_LOW(void);

interrupt_RBx_t RB4_obj = {
   .EXT_InterruptHandler_HIGH = RB4_Int_APP_ISR_HIGH,
   .EXT_InterruptHandler_LOW = RB4_Int_APP_ISR_LOW,
   .priority = INTERRUPT_HIGH_PRIORITY,
   .mcu_pin.direction = GPIO_DIRECTION_INPUT,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN4,
   .mcu_pin.port = PORTB_INDEX,  
};

interrupt_RBx_t RB5_obj = {
   .EXT_InterruptHandler_HIGH = RB5_Int_APP_ISR_HIGH,
   .EXT_InterruptHandler_LOW = RB5_Int_APP_ISR_LOW,
   .priority = INTERRUPT_HIGH_PRIORITY,
   .mcu_pin.direction = GPIO_DIRECTION_INPUT,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN5,
   .mcu_pin.port = PORTB_INDEX,  
};

interrupt_RBx_t RB6_obj = {
   .EXT_InterruptHandler_HIGH = RB6_Int_APP_ISR_HIGH,
   .EXT_InterruptHandler_LOW = RB6_Int_APP_ISR_LOW,
   .priority = INTERRUPT_HIGH_PRIORITY,
   .mcu_pin.direction = GPIO_DIRECTION_INPUT,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN6,
   .mcu_pin.port = PORTB_INDEX,  
};

interrupt_RBx_t RB7_obj = {
   .EXT_InterruptHandler_HIGH = RB7_Int_APP_ISR_HIGH,
   .EXT_InterruptHandler_LOW = RB7_Int_APP_ISR_LOW,
   .priority = INTERRUPT_HIGH_PRIORITY,
   .mcu_pin.direction = GPIO_DIRECTION_INPUT,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN7,
   .mcu_pin.port = PORTB_INDEX,  
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

led_t led_3 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .led_status = LED_OFF,
};

led_t led_4 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN3,
    .led_status = LED_OFF,
};


int main() {

    
    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    ret = led_initialize(&led_3);
    ret = led_initialize(&led_4);
    
    ret = Interrupt_RBx_Init(&RB4_obj);
    ret = Interrupt_RBx_Init(&RB5_obj);
    ret = Interrupt_RBx_Init(&RB6_obj);
    ret = Interrupt_RBx_Init(&RB7_obj);

    while (1)
    {
        
   
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ecu_layer_initialize();
}

void RB4_Int_APP_ISR_HIGH(void){
    ret = led_turn_on(&led_1);
}

void RB4_Int_APP_ISR_LOW(void){
    ret = led_turn_on(&led_2);
}

void RB5_Int_APP_ISR_HIGH(void){
    ret = led_turn_off(&led_1);
}

void RB5_Int_APP_ISR_LOW(void){
    ret = led_turn_off(&led_2);
}

void RB6_Int_APP_ISR_HIGH(void){
    ret = led_turn_on(&led_3);
}

void RB6_Int_APP_ISR_LOW(void){
    ret = led_turn_on(&led_4);
}

void RB7_Int_APP_ISR_HIGH(void){
    ret = led_turn_off(&led_3);
}

void RB7_Int_APP_ISR_LOW(void){
    ret = led_turn_off(&led_4);
}





