/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"



Std_ReturnType ret = E_NOT_OK;
void Application (void);
adc_result_t res_1 = ZERO_INIT;
uint8 adc_flag = ZERO_INIT;
void ADC_DefaultInterruptHandler(void);
adc_conf_t adc_1 = {
    .ADC_InterruptHandler = ADC_DefaultInterruptHandler,
    .Acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .convertion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISALBE,
};

void ADC_DefaultInterruptHandler(void){
    adc_flag++;
    ret = ADC_GetConversionResult(&adc_1,&res_1);
}




int main() {

    Application ();
    while (1)
    {
        ret = ADC_GetConversion_Interrupt (&adc_1, ADC_CHANNEL_AN0);
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ret = ADC_Init(&adc_1);
    ecu_layer_initialize();
}