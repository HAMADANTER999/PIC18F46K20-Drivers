/* 
 * File:   timer0.h
 * Author: anter
 *
 * Created on September 15, 2024, 6:31 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

/* Section : includes*/
#include "xc.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupts.h"

/* Section : Macro Declarations*/

#define TIMER0_PRESCALER_ENABLE_CFG    1U
#define TIMER0_PRESCALER_DISABLE_CFG   0U

#define TIMER0_RISING_EDGE_CFG         1U
#define TIMER0_FALLING_EDGE_CFG        0U

#define TIMER0_TIMER_MODE              1U
#define TIMER0_COUNTER_MODE            0U

#define TIMER0_8BIT_REGISTER_MODE      1U
#define TIMER0_16BIT_REGOSTER_MODE     0U

/* Section : Macro Function Declarations*/

#define TIMER0_PRESCALER_ENABLE()      (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()     (T0CONbits.PSA = 1)

#define TIMER0_RISING_EDGE_ENABLE()    (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE_ENABLE()   (T0CONbits.T0SE = 1)

#define TIMER0_TIMER_MODE_ENABLE()     (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()   (T0CONbits.T0CS = 1)

#define TIMER0_8BIT_REGISTER_MODE_ENABLE()     (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGOSTER_MODE_ENABLE()    (T0CONbits.T08BIT = 0)

#define TIMER0_MODULE_ENABLE()      (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()     (T0CONbits.TMR0ON = 0)

/* Section : Data type Declarations*/


typedef enum {
    TIMER0_PRESCALER_DIV_BY_2,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,   
}timer0_prescaler_select_t;
    
typedef struct {
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
    void (*TMR0_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    timer0_prescaler_select_t prescaler_value;
    uint16 timer0_preloaded_value;
    uint8 prescaler_enable : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_mode : 1;
    uint8 timer0_register_size : 1;
    uint8 timer0_reserved : 4;
}timer0_t;


/* Section : Function Declarations*/
Std_ReturnType Timer0_Init(const timer0_t *_timer);
Std_ReturnType Timer0_DeInit(const timer0_t *_timer);
Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 value);
Std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *value);

#endif	/* TIMER0_H */

