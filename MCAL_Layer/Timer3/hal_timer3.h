/* 
 * File:   hal_timer3.c
 * Author: anter
 *
 * Created on September 17, 2024, 5:23 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* Section : includes*/
#include "xc.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupts.h"
/* Section : Macro Declarations*/

/* Timer3 Clock Source (Timer or Counter) */
#define TIMER3_TIMER_MODE              0U
#define TIMER3_COUNTER_MODE            1U
/* Timer3 External Clock Input Synchronization*/
#define TIMER3_ASYNC_COUNTER_MODE      1U
#define TIMER3_SYNC_COUNTER_MODE       0U
/* Timer3 input clock pre-scaler */
#define TIMER3_PRESCALER_DIV_BY_1      0U
#define TIMER3_PRESCALER_DIV_BY_2      1U
#define TIMER3_PRESCALER_DIV_BY_4      2U
#define TIMER3_PRESCALER_DIV_BY_8      3U

#define TIMER3_RW_REG_8BIT_MODE     1U
#define TIMER3_RW_REG_16BIT_MODE    0U

/* Section : Macro Function Declarations*/

/* Enable Or Disable Timer3 Module */
#define TIMER3_MODULE_ENABLE()      (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()     (T3CONbits.TMR3ON = 0)
/* Timer3 Clock Source (Timer or Counter) */
#define TIMER3_TIMER_MODE_ENABLE()     (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()   (T3CONbits.TMR3CS = 1)
/* Timer3 External Clock Input Synchronization*/
#define TIMER3_ASYNC_COUNTER_MODE_ENABLE() (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()  (T3CONbits.T3SYNC = 0)
/* Timer3 input clock pre-scaler */
#define TIMER3_PRESCALER_SELECT(_PRESCALER_)    (T3CONbits.T3CKPS = _PRESCALER_)
/* Timer3 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_8BIT_MODE_ENABLE()      (T3CONbits.RD16 = 0)
#define TIMER3_RW_REG_16BIT_MODE_DISABLE()    (T3CONbits.RD16 = 1)


/* Section : Data type Declarations*/

typedef struct {
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
    void (*TMR3_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer3_preloaded_value;
    uint8 timer3_prescaler_value : 2;
    uint8 timer3_mode : 1;
    uint8 timer3_counter_mode : 1;
    uint8 timer3_reg_wr_mode : 1;
    uint8 timer3_reserved : 3;
}timer3_t;


/* Section : Function Declarations*/
Std_ReturnType Timer3_Init(const timer3_t *_timer);
Std_ReturnType Timer3_DeInit(const timer3_t *_timer);
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 value);
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *value);


#endif	/* HAL_TIMER3_H */

