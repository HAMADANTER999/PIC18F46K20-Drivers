/* 
 * File:   hal_ccp.c
 * Author: anter
 *
 * Created on September 19, 2024, 12:32 PM
 */
#include "hal_ccp.h"

#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
static void (*CCP1_InterruptHandler)(void) = NULL;
#endif

#ifdef CCP2_INTERRUPT_FEATURE_ENABLE
static void (*CCP2_InterruptHandler)(void) = NULL;
#endif

static Std_ReturnType CCP_Interrupt_Config(const ccp_t * _ccp_obj);
static Std_ReturnType CCP_PWM_Mode_Config(const ccp_t * _ccp_obj);
static void CCP_Mode_Timer_Select(const ccp_t * _ccp_obj);


Std_ReturnType CCP_Init(const ccp_t * _ccp_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        /* CCP Module Disable */
        if (CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if (CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else {/* Nothing */}
        
        /* CCP Module Capture Mode Initialization */
        if (CCP_CAPTURE_MODE_SELECTED == _ccp_obj->ccp_mode){
            /* CCP1 Module Capture variants Mode Initialization */
           switch (_ccp_obj->ccp_mode_variant){
               case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
               case CCP_CAPTURE_MODE_1_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE); break;
               case CCP_CAPTURE_MODE_4_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE); break;
               case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
               default : ret = E_NOT_OK; break;/* Not Supported Variant */
           }
           CCP_Mode_Timer_Select(_ccp_obj);
           
        }
        /* CCP1 Module Compare Mode Initialization */
        else if (CCP_COMPARE_MODE_SELECTED == _ccp_obj->ccp_mode){
            /* CCP1 Module Compare variants Mode Initialization */
            switch (_ccp_obj->ccp_mode_variant){
               case CCP_COMPARE_MODE_SET_PIN_LOW : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW); break;
               case CCP_COMPARE_MODE_SET_PIN_HIGH : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH); break;
               case CCP_COMPARE_MODE_TOGGLE_ON_MATCH : CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH); break;
               case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
               case CCP_COMPARE_MODE_GEN_EVENT : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT); break;
               default : ret = E_NOT_OK; break; /* Not Supported Variant */
           } 
            CCP_Mode_Timer_Select(_ccp_obj);
        }
        /* CCP1 Module PWM Mode Initialization */

        else if (CCP_PWM_MODE_SELECTED == _ccp_obj->ccp_mode){
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
        CCP_PWM_Mode_Config(_ccp_obj);
#endif 
        }
        else {/* Nothing */}
        /* Pin Configuration */
        ret = gpio_pin_intialize(&(_ccp_obj->pin));
        /* Interrupt Configuration */
        ret = CCP_Interrupt_Config(_ccp_obj);
     
    }
    return ret;
}
Std_ReturnType CCP_DeInit(const ccp_t * _ccp_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        /* CCP Module Disable */
        if (CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
            /* Interrupt Configuration */
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
            CCP1_InterruptDisable();
#endif
        }
        else if (CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
            /* Interrupt Configuration */
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE
            CCP2_InterruptDisable();
#endif
        }
        else {/* Nothing */}
    }
    return ret;
}

void CCP1_ISR(void){
    CCP1_InterruptFlagClear();
    if (CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
}
 


void CCP2_ISR(void){
    CCP1_InterruptFlagClear();
    if (CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
}

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP_IsCaptureDataReady(uint8 *_capture_status){
    Std_ReturnType ret = E_OK;
    if (NULL == _capture_status){
        ret = E_NOT_OK;
    }
    else{
        if (CCP_CAPTURE_READY == PIR1bits.CCP1IF){
            *_capture_status = CCP_CAPTURE_READY;
        }
        else {
            *_capture_status = CCP_CAPTURE_NOT_READY;
        }
            
            
        
    }
    return ret;
}
Std_ReturnType CCP_Capture_Mode_Read_value(uint16 *capture_value){
    Std_ReturnType ret = E_OK;
    CCP_REG_T capture_temp_value = {.ccpr_low = 0 , .ccpr_high = 0};
    if (NULL == capture_value){
        ret = E_NOT_OK;
    }
    else{
         capture_temp_value.ccpr_low = CCPR1L;
         capture_temp_value.ccpr_high = CCPR1H;
         *capture_value = capture_temp_value.ccpr_16bit;
    }
    return ret;
}
#endif 

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)
Std_ReturnType CCP_IsCompareComplete(uint8 *_compare_status){
    Std_ReturnType ret = E_OK;
    if (NULL == _compare_status){
        ret = E_NOT_OK;
    }
    else{
        if (CCP_COMPARE_READY == PIR1bits.CCP1IF){
            *_compare_status = CCP_COMPARE_READY;
        }
        else {
            *_compare_status = CCP_COMPARE_NOT_READY;
        }
    }
    return ret;
}
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t * _ccp_obj,uint16 compare_value){
    Std_ReturnType ret = E_OK;
    CCP_REG_T compare_temp_value = {.ccpr_low = 0 , .ccpr_high = 0};
    compare_temp_value.ccpr_16bit = compare_value;
    if (NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else {
        if (CCP1_INST == _ccp_obj->ccp_inst){
            CCPR1L = compare_temp_value.ccpr_low;
            CCPR1H = compare_temp_value.ccpr_high;
        }
        else if (CCP2_INST == _ccp_obj->ccp_inst){
            CCPR2L = compare_temp_value.ccpr_low;
            CCPR2H = compare_temp_value.ccpr_high;
        }
        else {/* Nothing */}
    }
    
    return ret;
}
#endif 

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t * _ccp_obj, const uint8 _duty){
    Std_ReturnType ret = E_OK;
    uint16 l_duty_temp = ZERO_INIT;
    l_duty_temp = (uint16)((PR2 + 1)*(_duty / 100.0) * 4);
    if (NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else {
        if (CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.DC1B = (uint8)( l_duty_temp & 0x03);
            CCPR1L = (uint8)(l_duty_temp >> 2);
        }
        else if (CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.DC2B = (uint8)( l_duty_temp & 0x03);
            CCPR2L = (uint8)(l_duty_temp >> 2);
        }
        else { /* Nothing */}    
    }
    return ret;
}
Std_ReturnType CCP_PWM_Start(const ccp_t * _ccp_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else {
        if (CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        }
        else if (CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        }
        else { /* Nothing */}    
    }
    return ret;
}
Std_ReturnType CCP_PWM_Stop(const ccp_t * _ccp_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else {
        if (CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        }
        else if (CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
        }
        else { /* Nothing */}    
    }
    return ret;
}
#endif 

static Std_ReturnType CCP_Interrupt_Config(const ccp_t * _ccp_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else {
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
        CCP1_InterruptEnable();
        CCP1_InterruptFlagClear();
        CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE     
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY ==_ccp_obj->CCP1_priority){
            INTERRUPT_GlobalInterruprHighEnable();
            CCP1_HighPrioritySet();
        }
        else if (INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP1_priority){
            INTERRUPT_GlobalInterruprLowEnable();
            CCP1_LowPrioritySet();
        }
        else { /* Nothing */ }
#else
        INTERRUPT_GlobalInterruprEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        
#endif

#ifdef CCP2_INTERRUPT_FEATURE_ENABLE
        CCP2_InterruptEnable();
        CCP2_InterruptFlagClear();
        CCP2_InterruptHandler = _ccp_obj->CCP2_InterruptHandler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE     
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY ==_ccp_obj->CCP2_priority){
            INTERRUPT_GlobalInterruprHighEnable();
            CCP2_HighPrioritySet();
        }
        else if (INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP2_priority){
            INTERRUPT_GlobalInterruprLowEnable();
            CCP2_LowPrioritySet();
        }
        else { /* Nothing */ }
#else
        INTERRUPT_GlobalInterruprEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        
#endif
    }
    return ret;
}
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED))
static Std_ReturnType CCP_PWM_Mode_Config(const ccp_t * _ccp_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else {
        if (CCP1_INST == _ccp_obj->ccp_inst){
            if (CCP_PWM_MODE == _ccp_obj->ccp_mode_variant){
               CCP1_SET_MODE(CCP_PWM_MODE);
            }
            else {/* Nothing */}
            }
        else if (CCP2_INST == _ccp_obj->ccp_inst){
            if (CCP_PWM_MODE == _ccp_obj->ccp_mode_variant){
                CCP2_SET_MODE(CCP_PWM_MODE);
            }
            else {/* Nothing */}
            }
        else {/* Nothing */}
        /* PWM Frequency Initialization */
        PR2 = (uint8)((_XTAL_FREQ/(_ccp_obj->PWM_Frequency * 4.0 * _ccp_obj->timer2_postscaler_value
        * _ccp_obj->timer2_prescaler_value)) - 1);
    }
    return ret;
}
#endif 

static void CCP_Mode_Timer_Select(const ccp_t * _ccp_obj){
    if (CCP1_CCP2_TIMER1 == _ccp_obj->ccp_capture_time){
        /* Timer1 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else if (CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_capture_time){
        /* Timer3 is the capture/compare clock source for CCP2 */
        /* Timer1 is the capture/compare clock source for CCP1 */
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if (CCP1_CCP2_TIMER3 == _ccp_obj->ccp_capture_time){
        /* Timer3 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    }
    else { /* Nothing */}
}