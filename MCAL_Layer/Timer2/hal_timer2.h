/* 
 * File:   hal_timer2.h
 * Author: anter
 *
 * Created on September 17, 2024, 12:30 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* Section : includes*/
#include "xc.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupts.h"

/* Section : Macro Declarations*/
/* Timer2 input clock post-scaler */
#define TIMER2_POSTSCALER_DIV_BY_1       0
#define TIMER2_POSTSCALER_DIV_BY_2       1
#define TIMER2_POSTSCALER_DIV_BY_3       2
#define TIMER2_POSTSCALER_DIV_BY_4       3
#define TIMER2_POSTSCALER_DIV_BY_5       4
#define TIMER2_POSTSCALER_DIV_BY_6       5
#define TIMER2_POSTSCALER_DIV_BY_7       6
#define TIMER2_POSTSCALER_DIV_BY_8       7
#define TIMER2_POSTSCALER_DIV_BY_9       8
#define TIMER2_POSTSCALER_DIV_BY_10      9
#define TIMER2_POSTSCALER_DIV_BY_11      10
#define TIMER2_POSTSCALER_DIV_BY_12      11
#define TIMER2_POSTSCALER_DIV_BY_13      12
#define TIMER2_POSTSCALER_DIV_BY_14      13
#define TIMER2_POSTSCALER_DIV_BY_15      14
#define TIMER2_POSTSCALER_DIV_BY_16      15

/* Timer2 input clock pre-scaler */
#define TIMER2_PRESCALER_DIV_BY_1         0
#define TIMER2_PRESCALER_DIV_BY_4         1
#define TIMER2_PRESCALER_DIV_BY_16        2

/* Section : Macro Function Declarations*/

/* Enable Or Disable Timer1 Module */
#define TIMER2_MODULE_ENABLE()      (T2CONbits.TMR2ON= 1)
#define TIMER2_MODULE_DISABLE()     (T2CONbits.TMR2ON = 0)

/* Timer2 input clock pre-scaler */
#define TIMER2_PRESCALER_SELECT(_PRESCALER_)    (T2CONbits.T2CKPS = _PRESCALER_)

/* Timer2 input clock post-scaler */
#define TIMER2_POSTSCALER_SELECT(_PRESCALER_)    (T2CONbits.T2OUTPS = _PRESCALER_)

/* Section : Data type Declarations*/
typedef struct {
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE
    void (*TMR2_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8 timer2_preloaded_value;
    uint8 timer2_postscaler_value : 4;
    uint8 timer2_prescaler_value : 2;
    uint8 timer2_reserved : 2;
}timer2_t;

/* Section : Function Declarations*/
Std_ReturnType Timer2_Init(const timer2_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 value);
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *value);


#endif	/* HAL_TIMER2_H */

