/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"



Std_ReturnType ret = E_NOT_OK;
void Application (void);

adc_conf_t adc_1 = {
    .ADC_InterruptHandler = NULL,
    .Acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .convertion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISALBE,
};

adc_result_t res_1 = ZERO_INIT, res_2 = ZERO_INIT, res_3 = ZERO_INIT , res_4 = ZERO_INIT;



int main() {

    Application ();
    while (1)
    {
        ret = ADC_GetConversion_Blocking (&adc_1, ADC_CHANNEL_AN0, &res_1);
        ret = ADC_GetConversion_Blocking (&adc_1, ADC_CHANNEL_AN1, &res_2);
        ret = ADC_GetConversion_Blocking (&adc_1, ADC_CHANNEL_AN2, &res_3);
        ret = ADC_GetConversion_Blocking (&adc_1, ADC_CHANNEL_AN3, &res_4);
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ret = ADC_Init(&adc_1);
    ecu_layer_initialize();
}