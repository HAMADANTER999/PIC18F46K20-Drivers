/* 
 * File:   hal_usart.c
 * Author: anter
 *
 * Created on September 25, 2024, 12:00 AM
 */

#include "hal_usart.h"

#ifdef EUSART_TX_INTERRUPT_FEATURE_ENABLE
static void (*EUSART_TXInterruptHandler)(void) = NULL;
#endif

#ifdef EUSART_RX_INTERRUPT_FEATURE_ENABLE
static void (*EUSART_RXInterruptHandler)(void) = NULL;
static void (*EUSART_FramingErrorHandler)(void) = NULL;
static void (*EUSART_OverrunErrorHandler)(void) = NULL;
#endif

static void EUSART_Baud_Rate_Calculations(const usart_t *_eusart);
static void EUSART_ASYN_TX_Init(const usart_t *_eusart);
static void EUSART_ASYN_RX_Init(const usart_t *_eusart);


Std_ReturnType EUSART_ASYN_Init(const usart_t *_eusart){
    Std_ReturnType ret = E_OK;
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else {
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        EUSART_Baud_Rate_Calculations(_eusart);
        EUSART_ASYN_TX_Init(_eusart);
        EUSART_ASYN_RX_Init(_eusart);
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE;
    }
    return ret;
}
Std_ReturnType EUSART_ASYN_DeInit(const usart_t *_eusart){
    Std_ReturnType ret = E_OK;
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else {
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
    }
    return ret;
}
Std_ReturnType EUSART_ASYN_ReadByteBlocking(uint8 * _data){
    Std_ReturnType ret = E_OK;
    if(NULL == _data){
        ret = E_NOT_OK;
    }
    else {
        while (!PIR1bits.RCIF);
        * _data = RCREG;
    }
    return ret;
}
Std_ReturnType EUSART_ASYN_WriteByteBlocking(uint8 _data){
    Std_ReturnType ret = E_OK;
    while (!TXSTAbits.TRMT);
#ifdef EUSART_TX_INTERRUPT_FEATURE_ENABLE
    EUSART_TX_InterruptEnable();
#endif
    TXREG = _data;
    return ret;
}
Std_ReturnType EUSART_ASYN_ReadByteNonBlocking(uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if (1 ==PIR1bits.RCIF){
        * _data = RCREG;
        ret = E_OK;
    }
    else {
        ret = E_NOT_OK;
    }
    return ret;
}
Std_ReturnType EUSART_ASYN_RX_Restart(void){
    Std_ReturnType ret = E_NOT_OK;
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;
    return ret;
}
void EUSART_TX_ISR(void){
#ifdef EUSART_TX_INTERRUPT_FEATURE_ENABLE
    EUSART_TX_InterruptDisable();
#endif 
    if (EUSART_TXInterruptHandler){
        EUSART_TXInterruptHandler();
    }
    else {/* Nothing */}
}
void EUSART_RX_ISR(void){
    if (EUSART_RXInterruptHandler){
        EUSART_RXInterruptHandler();
    }
    else {/* Nothing */}
    if (EUSART_FramingErrorHandler){
        EUSART_FramingErrorHandler();
    }
    else {/* Nothing */}
    if (EUSART_OverrunErrorHandler){
        EUSART_OverrunErrorHandler();
    }
    else {/* Nothing */}
            
}
Std_ReturnType EUSART_ASYN_WriteStringBlocking(uint8 *_data, uint16 str_len){
    Std_ReturnType ret = E_OK;
    uint16 char_counter = ZERO_INIT;
    for (char_counter = ZERO_INIT ; char_counter < str_len ; char_counter++){
        ret = EUSART_ASYN_WriteByteBlocking(_data[char_counter]);  
    }
        
    return ret;
}
static void EUSART_Baud_Rate_Calculations(const usart_t *_eusart){
    float Baud_Rate_Temp = 0;
    switch (_eusart->baudrate_config){
        case BAUDRATE_ASYN_8BIT_LOW_SPEED :
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 64) - 1;
        break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED :
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
        break;
        case BAUDRATE_ASYN_16BIT_LOW_SPEED :
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
        break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED :
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
        break;
        case BAUDRATE_SYN_8BIT :
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
        break;
        case BAUDRATE_SYN_16BIT :
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
        break;
        default : /* Nothing */ break; 
    }
    SPBRG = (uint8)((uint32)Baud_Rate_Temp);
    SPBRGH = (uint8)((uint32)Baud_Rate_Temp >> 8);
}

static void EUSART_ASYN_TX_Init(const usart_t *_eusart){
    if (EUSART_ASYNCHRONOUS_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        /* EUSART Transmit Interrupt Enable */
        if (EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
            EUSART_TXInterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
#ifdef EUSART_TX_INTERRUPT_FEATURE_ENABLE
            EUSART_TX_InterruptEnable();
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
            INTERRUPT_PriorityLevelsEnable();
            if (INTERRUPT_HIGH_PRIORITY == _eusart->usart_tx_cfg.usart_tx_priority){
                INTERRUPT_GlobalInterruprHighEnable();
                EUSART_TX_HighPrioritySet();
            }
            else if (INTERRUPT_LOW_PRIORITY == _eusart->usart_tx_cfg.usart_tx_priority){
                INTERRUPT_GlobalInterruprLowEnable();
                EUSART_TX_LowPrioritySet();
            }
            else { /* Nothing */ }
#else
        INTERRUPT_GlobalInterruprEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif             
#endif 
        }
        else if (EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
        }
        else { /* Nothing */}
        /* EUSART 9-bit Transmit Configuration */
        if (EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE;
        }
        else if (EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
        }
        else { /* Nothing */}
    }
    else { /* Nothing */}
}

static void EUSART_ASYN_RX_Init(const usart_t *_eusart){
    if (EUSART_ASYNCHRONOUS_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
        /* EUSART Receiver Interrupt Enable */
        if (EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
            EUSART_RXInterruptHandler = _eusart->EUSART_RxDefaultInterruptHandler;
            EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
            EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
#ifdef EUSART_RX_INTERRUPT_FEATURE_ENABLE
            EUSART_RX_InterruptEnable();
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
            INTERRUPT_PriorityLevelsEnable();
            if (INTERRUPT_HIGH_PRIORITY == _eusart->usart_rx_cfg.usart_rx_priority){
                INTERRUPT_GlobalInterruprHighEnable();
                EUSART_RX_HighPrioritySet();
            }
            else if (INTERRUPT_LOW_PRIORITY == _eusart->usart_rx_cfg.usart_rx_priority){
                INTERRUPT_GlobalInterruprLowEnable();
                EUSART_RX_LowPrioritySet();
            }
            else { /* Nothing */ }
#else
        INTERRUPT_GlobalInterruprEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif 
#endif 
        }
        else if (EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
        }
        else { /* Nothing */}
        /* EUSART 9-bit Receiver Configuration */
        if (EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
             RCSTAbits.RC9 = EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE;
        }
        else if (EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
             RCSTAbits.RC9 = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;
        }
        else { /* Nothing */}
    }
    else { /* Nothing */}
}
