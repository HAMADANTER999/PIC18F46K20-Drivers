/* 
 * File:   hal_timer2.c
 * Author: anter
 *
 * Created on September 17, 2024, 12:30 PM
 */
#include "hal_timer2.h"

#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE
static void (*TMR2_InterruptHandler)(void) = NULL;
#endif

static uint8 timer2_preload = ZERO_INIT;


Std_ReturnType Timer2_Init(const timer2_t *_timer){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER2_MODULE_DISABLE();
        TIMER2_PRESCALER_SELECT(_timer->timer2_prescaler_value);
        TIMER2_POSTSCALER_SELECT(_timer->timer2_postscaler_value);
        TMR2 = _timer->timer2_preloaded_value;
        timer2_preload = _timer->timer2_preloaded_value;
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        TMR2_InterruptHandler = _timer->TMR2_InterruptHandler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE     
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruprHighEnable();
            TIMER2_HighPrioritySet();
        }
        else if (INTERRUPT_LOW_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruprLowEnable();
            TIMER2_LowPrioritySet();
        }
        else { /* Nothing */ }
#else
        INTERRUPT_GlobalInterruprEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        
#endif
        TIMER2_MODULE_ENABLE();
        
    }
    return ret;
}
Std_ReturnType Timer2_DeInit(const timer2_t *_timer){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER2_MODULE_DISABLE();
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptDisable();
#endif
    }
    return ret;
}
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 value){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = value;
    }
    return ret;
}
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *value){
    Std_ReturnType ret = E_OK;
    if ((NULL == _timer) && (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        *value = TMR2;
    }
    return ret;
}

void TMR2_ISR(void){
    TIMER2_InterruptFlagClear();
    TMR2 = timer2_preload;
    if (TMR2_InterruptHandler){
        TMR2_InterruptHandler();
    }
}