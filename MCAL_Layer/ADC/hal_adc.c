/* 
 * File:   hal_adc.c
 * Author: anter
 *
 * Created on August 30, 2024, 10:56 AM
 */

#include "hal_adc.h"
#ifdef ADC_INTERRUPT_FEATURE_ENABLE
static void (* ADC_InterruptHandler) (void) = NULL;
#endif 
 

static inline Std_ReturnType adc_input_channel_port_configure(adc_channel_select_t channel);
static inline Std_ReturnType select_result_format(const adc_conf_t *_adc);
static inline Std_ReturnType configure_voltage_reference(const adc_conf_t *_adc);

/**
 * @Summary initialize the  ADC
 * @Description this routine initialize the  ADC
 *              this routine is called before any other ADC routine is called 
 *              this routine should only be called once during the system initialization 
 * @preconditions none 
 * @param _adc pointer to the ADC configurations 
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType ADC_Init(const adc_conf_t *_adc){
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        /* Configure the Acquisition time */
        ADCON2bits.ACQT = _adc->Acquisition_time;
        /* Configure the conversion Clock */
        ADCON2bits.ADCS = _adc->convertion_clock;
        /* Configure the default channel */
        ADCON0bits.CHS = _adc->adc_channel;
        adc_input_channel_port_configure(_adc->adc_channel);
        /* Configure the interrupt */
#ifdef ADC_INTERRUPT_FEATURE_ENABLE
        INTERRUPT_GlobalInterruprEnable();
        INTERRUPT_PeripheralInterruptEnable();
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
        if (INTERRUPT_HIGH_PRIORITY == _adc->priority) {ADC_HighPrioritySet();}
        else if (INTERRUPT_LOW_PRIORITY == _adc->priority) {ADC_LowPrioritySet();}
        else {/* Nothing */ }
#endif     
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;
#endif 
        /* Configure the result format */
        select_result_format(_adc);
        /* Configure the voltage reference */
        configure_voltage_reference(_adc);
        /* Enable the ADC */
        ADC_CONVERTER_ENABLE();
    }
    return ret;
}
/**
 * @Summary De-initialize the ADC
 * @param _adc pointer to the ADC configurations 
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc){
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        /* Disable the interrupt */
#ifdef ADC_INTERRUPT_FEATURE_ENABLE
        ADC_InterruptDisable();
#endif
        
    }
    return ret;
}

/**
 * @Summary Allow selection of a channel for conversion  
 * @description this routine is used to select desired channel for conversion
 * @preconditions ADC_Init() function should have been called before calling this function 
 * @param _adc pointer to the ADC configurations 
 * @param channel defines the channel available for conversion 
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType ADC_SelectChannel (const adc_conf_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel);
    }
    return ret;
}
/**
 * @Summary start conversion 
 * @description this routine is used to start conversion of desired channel 
 * @preconditions ADC_Init() function should have been called before calling this function
 * @param _adc pointer to the ADC configurations 
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType ADC_StartConversion (const adc_conf_t *_adc){
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_START_CONVERSION();
    }
    return ret;
}
/**
 * @Summary Returns true when the conversion is completed otherwise false 
 * @Description this routine is used to determine if the conversion is completed 
 *              when the conversion is completed routine returns true. it returns false otherwise  
 * @preconditions ADC_Init() function should have been called before calling this function
 *                ADC_StartConversion() should have been called before calling this function 
 * @param _adc pointer to the ADC configurations 
 * @param conversion_status returns the conversion status
 *          true - If conversion is completed
 *          false - If conversion is not completed 
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */

Std_ReturnType ADC_IsConversionDone (const adc_conf_t *_adc, uint8 *conversion_status){
    Std_ReturnType ret = E_OK;
    if ((NULL == _adc) || (NULL == conversion_status))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
    }
    return ret;
}
/**
 * @Summary Returns the ADC conversion value.
 * @Description This routine is used to get the analog to digital converted value.
 *              This routine gets converted values from the channel specified.
 * @Preconditions   This routine returns the conversion value only after the conversion is complete.
 *                  Completion status can be checked using ADC_IsConversionDone() routine.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversionResult (const adc_conf_t *_adc, adc_result_t *conversion_result){
    Std_ReturnType ret = E_OK;
    if ((NULL == _adc) || (NULL == conversion_result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        if (ADC_RESULT_RIGHT == _adc->result_format)
        {
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL );
        }
        else if (ADC_RESULT_LEFT == _adc->result_format)
        {
            *conversion_result = (adc_result_t)(((ADRESH << 8) + ADRESL ) >> 6 ) ;
        }
        else
        {
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL );
        }
    }
    return ret;
}
/**
 * @Summary Returns the ADC conversion value, also allows selection of a channel for conversion.
 * @Description This routine is used to select desired channel for conversion.
 *              This routine is get the analog to digital converted value.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversion_Blocking (const adc_conf_t *_adc, adc_channel_select_t channel,
                                  adc_result_t *conversion_result){
    Std_ReturnType ret = E_OK;
    if ((NULL == _adc) || (NULL == conversion_result))
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* select the A/D channel */
        ret = ADC_SelectChannel (_adc, channel);
        /* start the conversion */
        ret |= ADC_StartConversion (_adc);
        /* check if conversion is completed */
        while (ADCON0bits.GO_nDONE);
        ret = ADC_GetConversionResult(_adc, conversion_result);
            
    }
    return ret;
}

Std_ReturnType ADC_GetConversion_Interrupt (const adc_conf_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* select the A/D channel */
        ret = ADC_SelectChannel (_adc, channel);
        /* start the conversion */
        ret |= ADC_StartConversion (_adc);    
    }
    return ret;
}
static inline Std_ReturnType adc_input_channel_port_configure(adc_channel_select_t channel){
    Std_ReturnType ret = E_OK;
    switch (channel)
    {
        case ADC_CHANNEL_AN0  : SET_BIT(TRISA, _TRISA_RA0_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN1  : SET_BIT(TRISA, _TRISA_RA1_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN2  : SET_BIT(TRISA, _TRISA_RA2_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN3  : SET_BIT(TRISA, _TRISA_RA3_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN4  : SET_BIT(TRISA, _TRISA_RA5_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN5  : SET_BIT(TRISE, _TRISE_RE0_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN6  : SET_BIT(TRISE, _TRISE_RE1_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN7  : SET_BIT(TRISE, _TRISE_RE2_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN8  : SET_BIT(TRISB, _TRISB_RB2_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN9  : SET_BIT(TRISB, _TRISB_RB3_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, _TRISB_RB1_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB, _TRISB_RB4_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB, _TRISB_RB0_POSN); break; /* Disable the digital output driver */
        default : ret = E_NOT_OK;
    }
    return ret;
}

static inline Std_ReturnType select_result_format(const adc_conf_t *_adc){
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if (ADC_RESULT_RIGHT == _adc->result_format)
        {
            ADC_RESULT_RIGHT_FORMAT();
        }
        else if (ADC_RESULT_LEFT == _adc->result_format)
        {
            ADC_RESULT_LEFT_FORMAT();
        }
        else
        {
            ADC_RESULT_RIGHT_FORMAT();
        }    
    }
    return ret;
}

static inline Std_ReturnType configure_voltage_reference(const adc_conf_t *_adc){
    Std_ReturnType ret = E_OK;
    if (NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if (ADC_VOLTAGE_REFERENCE_ENALBE == _adc->voltage_reference)
        {
            ADC_ENALBE_VOLTAGE_REFERENCE();
        }
        else if (ADC_VOLTAGE_REFERENCE_DISALBE == _adc->voltage_reference)
        {
            ADC_DIALBE_VOLTAGE_REFERENCE();
        }
        else
        {
            ADC_DIALBE_VOLTAGE_REFERENCE();
        }    
    }
    return ret;
}
void ADC_ISR(void){
    ADC_InterruptFlagClear();
    if (ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
}