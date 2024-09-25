/* 
 * File:   hal_usart.h
 * Author: anter
 *
 * Created on September 25, 2024, 12:00 AM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* Section : includes*/
#include "xc.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupts.h"
#include "hal_usart_cfg.h"

/* Section : Macro Declarations*/
/* Selecting UART Working Mode */
#define EUSART_SYNCHRONOUS_MODE               1
#define EUSART_ASYNCHRONOUS_MODE              0
/* Baud rate generator Asynchronous speed mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED        1
#define EUSART_ASYNCHRONOUS_LOW_SPEED         0
/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE         1
#define EUSART_ASYNCHRONOUS_TX_DISABLE        0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE         1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE        0
/* EUSART 9-bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE         1
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE        0
/* Baud rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN             1
#define EUSART_08BIT_BAUDRATE_GEN             0
/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE         1
#define EUSART_ASYNCHRONOUS_RX_DISABLE        0
/* EUSART Receiver Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE         1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE        0
/* EUSART 9-bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE         1
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE        0
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED     1
#define EUSART_FRAMING_ERROR_CLEARED      0
/* EUSART Overrun Error */
#define EUSART_OVERUN_ERROR_DETECTED     1
#define EUSART_OVERUN_ERROR_CLEARED      0


/* Section : Macro Function Declarations*/


/* Section : Data type Declarations*/

typedef enum {
    BAUDRATE_ASYN_8BIT_LOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_LOW_SPEED,
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT,
}baudrate_gen_t;

typedef struct {
    uint8 usart_reserved : 5;
    uint8 usart_tx_enable : 1;
    uint8 usart_tx_interrupt_enable : 1;
    uint8 usart_tx_9bit_enable : 1;
}usart_tx_cfg_t;

typedef union {
    struct {
        uint8 usart_reserved : 6;
        uint8 usart_ferr : 1;
        uint8 usart_oerr : 1;
    };
    uint8 status;
}usart_error_status_T;

typedef struct {
    uint8 usart_reserved : 5;
    uint8 usart_rx_enable : 1;
    uint8 usart_rx_interrupt_enable : 1;
    uint8 usart_rx_9bit_enable : 1;
}usart_rx_cfg_t;

typedef struct {
    void (*EUSART_TxDefaultInterruptHandler)(void);
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
    uint32 baudrate;
    baudrate_gen_t baudrate_config;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_T error_status;
}usart_t; 

/* Section : Function Declarations*/

Std_ReturnType EUSART_Init(const usart_t *_eusart);
Std_ReturnType EUSART_DeInit(const usart_t *_eusart);
Std_ReturnType EUSART_ReadByteBlocking(const usart_t *_eusart, uint8 * _data);
Std_ReturnType EUSART_WriteByteBlocking(const usart_t *_eusart, uint8 _data);


#endif	/* HAL_USART_H */

