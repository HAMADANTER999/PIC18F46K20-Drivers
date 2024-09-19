/* 
 * File:   hal_ccp1.c
 * Author: anter
 *
 * Created on September 19, 2024, 12:32 PM
 */
#include "hal_ccp1.h"

#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
static void (*CCP1_InterruptHandler)(void) = NULL;
#endif

Std_ReturnType CCP1_Init(const ccp1_t * _ccp_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        /* CCP1 Module Disable */
        CCP1_SET_MODE(CCP1_MODULE_DISABLE);
        /* CCP1 Module Capture Mode Initialization */
        if (CCP1_CAPTURE_MODE_SELECTED == _ccp_obj->ccp1_mode){
            /* CCP1 Module Capture variants Mode Initialization */
           switch (_ccp_obj->ccp1_mode_variant){
               case CCP1_CAPTURE_MODE_1_FALLING_EDGE : CCP1_SET_MODE(CCP1_CAPTURE_MODE_1_FALLING_EDGE); break;
               case CCP1_CAPTURE_MODE_1_RISING_EDGE : CCP1_SET_MODE(CCP1_CAPTURE_MODE_1_RISING_EDGE); break;
               case CCP1_CAPTURE_MODE_4_RISING_EDGE : CCP1_SET_MODE(CCP1_CAPTURE_MODE_4_RISING_EDGE); break;
               case CCP1_CAPTURE_MODE_16_RISING_EDGE : CCP1_SET_MODE(CCP1_CAPTURE_MODE_16_RISING_EDGE); break;
               default : ret = E_NOT_OK; break;/* Not Supported Variant */
           } 
        }
        /* CCP1 Module Compare Mode Initialization */
        else if (CCP1_COMPARE_MODE_SELECTED == _ccp_obj->ccp1_mode){
            /* CCP1 Module Compare variants Mode Initialization */
            switch (_ccp_obj->ccp1_mode_variant){
               case CCP1_COMPARE_MODE_SET_PIN_LOW : CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_LOW); break;
               case CCP1_COMPARE_MODE_SET_PIN_HIGH : CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_HIGH); break;
               case CCP1_COMPARE_MODE_TOGGLE_ON_MATCH : CCP1_SET_MODE(CCP1_COMPARE_MODE_TOGGLE_ON_MATCH); break;
               case CCP1_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_SW_INTERRUPT); break;
               case CCP1_COMPARE_MODE_GEN_EVENT : CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_EVENT); break;
               default : ret = E_NOT_OK; break; /* Not Supported Variant */
           }  
        }
        /* CCP1 Module PWM Mode Initialization */
        else if (CCP1_PWM_MODE_SELECTED == _ccp_obj->ccp1_mode){
#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED)
            if (CCP1_PWM_MODE == _ccp_obj->ccp1_mode_variant){
                CCP1_SET_MODE(CCP1_PWM_MODE);
            }
            else {/* Nothing */}
            /* PWM Frequency Initialization */
            PR2 = (uint8)((_XTAL_FREQ/(_ccp_obj->PWM_Frequency * 4.0 * _ccp_obj->timer2_postscaler_value
                   * _ccp_obj->timer2_prescaler_value)) - 1);
#endif 
        }
        else {/* Nothing */}
        /* Pin Configuration */
        ret = gpio_pin_intialize(&(_ccp_obj->pin));
        /* Interrupt Configuration */
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
        CCP1_InterruptEnable();
        CCP1_InterruptFlagClear();
        CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE     
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY ==_ccp_obj->priority){
            INTERRUPT_GlobalInterruprHighEnable();
            CCP1_HighPrioritySet();
        }
        else if (INTERRUPT_LOW_PRIORITY == _ccp_obj->priority){
            INTERRUPT_GlobalInterruprLowEnable();
            CCP1_LowPrioritySet();
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
Std_ReturnType CCP1_DeInit(const ccp1_t * _ccp_obj){
    Std_ReturnType ret = E_OK;
    if (NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        /* CCP1 Module Disable */
        CCP1_SET_MODE(CCP1_MODULE_DISABLE);
        /* Interrupt Configuration */
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
        CCP1_InterruptDisable();
#endif
    }
    return ret;
}

#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP1_IsCaptureDataReady(uint8 *_capture_status){
    Std_ReturnType ret = E_OK;
    if (NULL == _capture_status){
        ret = E_NOT_OK;
    }
    else{
        if (CCP1_CAPTURE_READY == PIR1bits.CCP1IF){
            *_capture_status = CCP1_CAPTURE_READY;
        }
        else {
            *_capture_status = CCP1_CAPTURE_NOT_READY;
        }
            
            
        
    }
    return ret;
}
Std_ReturnType CCP1_Capture_Mode_Read_value(uint16 *capture_value){
    Std_ReturnType ret = E_OK;
    CCP1_REG_T capture_temp_value = {.ccpr1_low = 0 , .ccpr1_high = 0};
    if (NULL == capture_value){
        ret = E_NOT_OK;
    }
    else{
         capture_temp_value.ccpr1_low = CCPR1L;
         capture_temp_value.ccpr1_high = CCPR1H;
         *capture_value = capture_temp_value.ccpr1_16bit;
    }
    return ret;
}
#endif 

#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED)
Std_ReturnType CCP1_IsCompareComplete(uint8 *_compare_status){
    Std_ReturnType ret = E_OK;
    if (NULL == _compare_status){
        ret = E_NOT_OK;
    }
    else{
        if (CCP1_COMPARE_READY == PIR1bits.CCP1IF){
            *_compare_status = CCP1_COMPARE_READY;
        }
        else {
            *_compare_status = CCP1_COMPARE_NOT_READY;
        }
    }
    return ret;
}
Std_ReturnType CCP1_Compare_Mode_Set_Value(uint16 compare_value){
    Std_ReturnType ret = E_OK;
    CCP1_REG_T compare_temp_value = {.ccpr1_low = 0 , .ccpr1_high = 0};
    compare_temp_value.ccpr1_16bit = compare_value;
    CCPR1L = compare_temp_value.ccpr1_low;
    CCPR1H = compare_temp_value.ccpr1_high;
    return ret;
}
#endif 

#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP1_PWM1_Set_Duty(const uint8 _duty){
    Std_ReturnType ret = E_OK;
    uint16 l_duty_temp = ZERO_INIT;
    l_duty_temp = (uint16)((PR2 + 1)*(_duty / 100.0) * 4);
    CCP1CONbits.DC1B = (uint8)( l_duty_temp & 0x03);
    CCPR1L = (uint8)(l_duty_temp >> 2);
    return ret;
}
Std_ReturnType CCP1_PWM1_Start(void){
    Std_ReturnType ret = E_OK;
    CCP1CONbits.CCP1M = CCP1_PWM_MODE;
    return ret;
}
Std_ReturnType CCP1_PWM1_Stop(void){
    Std_ReturnType ret = E_OK;
    CCP1CONbits.CCP1M = CCP1_MODULE_DISABLE;
    return ret;
}
#endif 
