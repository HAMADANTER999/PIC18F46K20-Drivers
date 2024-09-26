/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

void application_intialize(void);
volatile uint32 valid_usart_counter = ZERO_INIT;

void EUSART_TxDefaultInterruptHandler(void);
void usart_module_init(void){
    Std_ReturnType ret = E_OK;
    usart_t usart_obj;
    usart_obj.EUSART_FramingErrorHandler = NULL;
    usart_obj.EUSART_OverrunErrorHandler = NULL;
    usart_obj.EUSART_RxDefaultInterruptHandler = NULL;
    usart_obj.EUSART_TxDefaultInterruptHandler = NULL;
    usart_obj.baudrate = 9600;
    usart_obj.baudrate_config = BAUDRATE_ASYN_8BIT_LOW_SPEED;
    
    usart_obj.usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
    
    usart_obj.usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;
    ret = EUSART_ASYN_Init(&usart_obj);
}

void usart_module_int_init(void){
    Std_ReturnType ret = E_OK;
    usart_t usart_obj;
    usart_obj.EUSART_FramingErrorHandler = NULL;
    usart_obj.EUSART_OverrunErrorHandler = NULL;
    usart_obj.EUSART_RxDefaultInterruptHandler = NULL;
    usart_obj.EUSART_TxDefaultInterruptHandler = EUSART_TxDefaultInterruptHandler;
    usart_obj.baudrate = 9600;
    usart_obj.baudrate_config = BAUDRATE_ASYN_8BIT_LOW_SPEED;
    
    usart_obj.usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
    
    usart_obj.usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;
    ret = EUSART_ASYN_Init(&usart_obj);
}

led_t led_1 = {
  .led_status = LED_OFF,
  .pin = GPIO_PIN0,
  .port_name = PORTD_INDEX,
};
uint8 rec_uart_data = ZERO_INIT;
int main() { 
    Std_ReturnType ret = E_NOT_OK;
    
//    application_intialize();
    usart_module_int_init();
    ret = led_initialize(&led_1);
    
    
    while(1){   
          ret = EUSART_ASYN_WriteStringBlocking("Hello\r", 6);
//        ret = EUSART_ASYN_ReadByteNonBlocking(&rec_uart_data);
//        if (E_OK == ret){
//            if ('a' == rec_uart_data){
//                ret = led_turn_on(&led_1);
//                ret = EUSART_ASYN_WriteStringBlocking("LED_ON\r", 8);
//            }
//            else if ('b' == rec_uart_data){
//                ret = led_turn_off(&led_1);
//                ret = EUSART_ASYN_WriteStringBlocking("LED_OFF\r", 9);
//            }
//            else {/* Nothing */}
//        }
//        else {/* Nothing */}
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_initialize();
}


void EUSART_TxDefaultInterruptHandler(void){
   //led_turn_toggle(&led_1);
    valid_usart_counter++;
}


