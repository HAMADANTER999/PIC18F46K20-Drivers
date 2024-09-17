/* 
 * File:   hal_timer3.c
 * Author: anter
 *
 * Created on September 17, 2024, 5:23 PM
 */
#include "hal_timer3.h"

#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
static void (*TMR3_InterruptHandler)(void) = NULL;
#endif

static uint16 timer3_preload = ZERO_INIT;

static inline void Timer3_Mode_Select(const timer3_t *_timer);

Std_ReturnType Timer3_Init(const timer3_t *_timer){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_MODULE_DISABLE();
        TIMER3_PRESCALER_SELECT(_timer->timer3_prescaler_value);
        Timer3_Mode_Select(_timer);
        TMR3H = ((_timer->timer3_preloaded_value) >> 8);
        TMR3L = (uint8)(_timer->timer3_preloaded_value);
        timer3_preload = _timer->timer3_preloaded_value;
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        TMR3_InterruptHandler = _timer->TMR3_InterruptHandler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE     
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruprHighEnable();
            TIMER3_HighPrioritySet();
        }
        else if (INTERRUPT_LOW_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruprLowEnable();
            TIMER3_LowPrioritySet();
        }
        else { /* Nothing */ }
#else
        INTERRUPT_GlobalInterruprEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        
#endif
        TIMER3_MODULE_ENABLE();
    }
    return ret;
}
Std_ReturnType Timer3_DeInit(const timer3_t *_timer){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_MODULE_DISABLE();
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptDisable();
#endif
    }
    return ret;
}
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 value){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR3H = ((value) >> 8);
        TMR3L = (uint8)(value) ;
    }
    return ret;
}
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 l_tmr3l = ZERO_INIT, l_tmr3h = ZERO_INIT;
    if ((NULL == _timer) && (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        *value = (uint16)((l_tmr3h << 8 ) + l_tmr3l);
    }
    return ret;
}

void TMR3_ISR(void){
    TIMER3_InterruptFlagClear();
    TMR3H = ((timer3_preload) >> 8);
    TMR3L = (uint8)(timer3_preload) ;
    if (TMR3_InterruptHandler){
        TMR3_InterruptHandler();
    }
}

static inline void Timer3_Mode_Select(const timer3_t *_timer){
    if (TIMER3_TIMER_MODE  == _timer->timer3_mode){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if (TIMER3_COUNTER_MODE == _timer->timer3_mode){
        TIMER3_COUNTER_MODE_ENABLE();  
        if (TIMER3_ASYNC_COUNTER_MODE == _timer->timer3_counter_mode){
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if (TIMER3_SYNC_COUNTER_MODE == _timer->timer3_counter_mode){
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else { /* Nothing */ }        
    }
    else { /* Nothing */ }
    
}
