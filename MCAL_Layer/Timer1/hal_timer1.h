/* 
 * File:   hal_timer1.h
 * Author: anter
 *
 * Created on September 16, 2024, 6:35 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* Section : includes*/
#include "xc.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupts.h"

/* Section : Macro Declarations*/
/* Timer1 Clock Source (Timer or Counter) */
#define TIMER1_TIMER_MODE              0U
#define TIMER1_COUNTER_MODE            1U
/* Timer1 External Clock Input Synchronization*/
#define TIMER1_ASYNC_COUNTER_MODE      1U
#define TIMER1_SYNC_COUNTER_MODE       0U
/* Timer1 Oscillator */
#define TIMER1_OSC_ENABLE     1U
#define TIMER1_OSC_DISABLE    0U

/* Timer1 input clock pre-scaler */
#define TIMER1_PRESCALER_DIV_BY_1      0U
#define TIMER1_PRESCALER_DIV_BY_2      1U
#define TIMER1_PRESCALER_DIV_BY_4      2U
#define TIMER1_PRESCALER_DIV_BY_8      3U
/* 16-Bit Read/Write Mode */
#define TIMER1_RW_REG_8BIT_MODE     1U
#define TIMER1_RW_REG_16BIT_MODE    0U

/* Section : Macro Function Declarations*/
/* Enable Or Disable Timer1 Module */
#define TIMER1_MODULE_ENABLE()      (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()     (T1CONbits.TMR1ON = 0)
/* Timer1 Clock Source (Timer or Counter) */
#define TIMER1_TIMER_MODE_ENABLE()     (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()   (T1CONbits.TMR1CS = 1)
/* Timer1 External Clock Input Synchronization*/
#define TIMER1_ASYNC_COUNTER_MODE_ENABLE() (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()  (T1CONbits.T1SYNC = 0)
/* Timer1 Oscillator */
#define TIMER1_OSC_HW_ENABLE()      (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE()     (T1CONbits.T1OSCEN = 0)
/* Timer1 input clock pre-scaler */
#define TIMER1_PRESCALER_SELECT(_PRESCALER_)    (T1CONbits.T1CKPS = _PRESCALER_)
/* Timer1 System Clock Status*/
#define TIMER1_SYSTEM_CLOCK_STATUS()       (T1CONbits.T1RUN)
/* 16-Bit Read/Write Mode */
#define TIMER1_RW_REG_8BIT_MODE_ENABLE()      (T1CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BIT_MODE_DISABLE()    (T1CONbits.RD16 = 1)

/* Section : Data type Declarations*/



typedef struct {
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
    void (*TMR1_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer1_preloaded_value;
    uint8 timer1_prescaler_value : 2;
    uint8 timer1_mode : 1;
    uint8 timer1_counter_mode : 1;
    uint8 timer1_osc_cfg : 1;
    uint8 timer1_reg_wr_mode : 1;
    uint8 timer1_reserved : 2;
}timer1_t;

/* Section : Function Declarations*/
Std_ReturnType Timer1_Init(const timer1_t *_timer);
Std_ReturnType Timer1_DeInit(const timer1_t *_timer);
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 value);
Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *value);



#endif	/* HAL_TIMER1_H */

