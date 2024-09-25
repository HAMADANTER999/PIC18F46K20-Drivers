/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

void application_intialize(void);

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
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
    
    usart_obj.usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;
    ret = EUSART_Init(&usart_obj);
}

int main() { 
    Std_ReturnType ret = E_NOT_OK;
    
    application_intialize();

    while(1){    
        
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_initialize();
}


