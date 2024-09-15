/* 
 * File:   timer0.c
 * Author: anter
 *
 * Created on September 15, 2024, 6:31 PM
 */

#include "timer0.h"

#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
static void (*TMR0_InterruptHandler)(void) = NULL;
#endif

static uint16 timer0_preload = ZERO_INIT;

static inline void timer0_prescaler_config(const timer0_t *_timer);
static inline void Timer0_Mode_Select(const timer0_t *_timer);
static inline void Timer0_Register_Size_Config(const timer0_t *_timer);


Std_ReturnType Timer0_Init(const timer0_t *_timer){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
        timer0_prescaler_config(_timer);
        Timer0_Mode_Select(_timer);
        Timer0_Register_Size_Config(_timer);
        TMR0H = ((_timer->timer0_preloaded_value) >> 8);
        TMR0L = (uint8)(_timer->timer0_preloaded_value) ;
        timer0_preload = _timer->timer0_preloaded_value;
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
        
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        TMR0_InterruptHandler = _timer->TMR0_InterruptHandler;
 #ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruprHighEnable();
            TIMER0_HighPrioritySet();
        }
        else if (INTERRUPT_LOW_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruprLowEnable();
            TIMER0_LowPrioritySet();
        }
        else { /* Nothing */ }
#else
        INTERRUPT_GlobalInterruprEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
            
 #endif
        
        TIMER0_MODULE_ENABLE();
    }
    return ret;
    
}
Std_ReturnType Timer0_DeInit(const timer0_t *_timer){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
        #ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptDisable();
        #endif
    }
    return ret;
}
Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 value){
    Std_ReturnType ret = E_OK;
    if (NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR0H = ((value) >> 8);
        TMR0L = (uint8)(value) ;
    }
    return ret;
}
Std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 l_tmr0l = ZERO_INIT, l_tmr0h = ZERO_INIT;
    if ((NULL == _timer) && (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *value = (uint16)((l_tmr0h << 8 ) + l_tmr0l);
    }
    return ret;
}

void TMR0_ISR(void){
    TIMER0_InterruptFlagClear();
    TMR0H = ((timer0_preload) >> 8);
    TMR0L = (uint8)(timer0_preload) ;
    if (TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
}

static inline void timer0_prescaler_config(const timer0_t *_timer){
    if (TIMER0_PRESCALER_ENABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if (TIMER0_PRESCALER_DISABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_DISABLE();
    }
    else { /* Nothing */ }
}

static inline void Timer0_Mode_Select(const timer0_t *_timer){
    if (TIMER0_TIMER_MODE  == _timer->timer0_mode){
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if (TIMER0_COUNTER_MODE == _timer->timer0_mode){
        TIMER0_COUNTER_MODE_ENABLE();
        if (TIMER0_RISING_EDGE_CFG == _timer->timer0_counter_edge){
            TIMER0_RISING_EDGE_ENABLE();
        }
        else if (TIMER0_FALLING_EDGE_CFG == _timer->timer0_counter_edge){
            TIMER0_FALLING_EDGE_ENABLE();
        }   
        else { /* Nothing */ }
    }
    else { /* Nothing */ }
}

static inline void Timer0_Register_Size_Config(const timer0_t *_timer){
    if (TIMER0_8BIT_REGISTER_MODE == _timer->timer0_register_size){
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
    else if (TIMER0_16BIT_REGOSTER_MODE == _timer->timer0_register_size){
        TIMER0_16BIT_REGOSTER_MODE_ENABLE();
    }
    else { /* Nothing */ }
}
    