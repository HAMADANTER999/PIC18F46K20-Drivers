/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

void Application (void);
void ADC_DefaultInterruptHandler(void);

adc_conf_t adc_1 = {
    .ADC_InterruptHandler = ADC_DefaultInterruptHandler,
    .Acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .convertion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISALBE,
};

chr_lcd_4bit_t lcd_1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW
};

dc_motor_t motor_1 = {
   .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
   .dc_motor[0].logic = GPIO_LOW,
   .dc_motor[0].pin = GPIO_PIN0,
   .dc_motor[0].port = PORTD_INDEX,
   .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT,
   .dc_motor[1].logic = GPIO_LOW,
   .dc_motor[1].pin = GPIO_PIN1,
   .dc_motor[1].port = PORTD_INDEX,
};
dc_motor_t motor_2 = {
   .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
   .dc_motor[0].logic = GPIO_LOW,
   .dc_motor[0].pin = GPIO_PIN2,
   .dc_motor[0].port = PORTD_INDEX,
   .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT,
   .dc_motor[1].logic = GPIO_LOW,
   .dc_motor[1].pin = GPIO_PIN3,
   .dc_motor[1].port = PORTD_INDEX,
};
        
Std_ReturnType ret = E_NOT_OK;
adc_result_t res_1 = ZERO_INIT, res_2 = ZERO_INIT, lm35_res_1_Celsius = ZERO_INIT,lm35_res_2_Celsius = ZERO_INIT  ;
uint8 adc_res_1_txt[6], adc_res_2_txt[6];
uint8 ADC_Req = ZERO_INIT;
int main() {
    Application ();
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 7, "LM35 Test");
    
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "Temp1: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3, 1, "Temp2: ");

    
    while (1)
    {
        if (0 == ADC_Req){
            ret = ADC_GetConversion_Interrupt (&adc_1, ADC_CHANNEL_AN0);
        }
        else if (1 == ADC_Req){
            ret = ADC_GetConversion_Interrupt (&adc_1, ADC_CHANNEL_AN1);
        }
        else { /* Nothing */ }
        
        lm35_res_1_Celsius = res_1 * 4.88f;
        lm35_res_2_Celsius = res_2 * 4.88f;
        
        lm35_res_1_Celsius /= 10;
        lm35_res_2_Celsius /= 10;
        
        ret = convert_short_to_string(lm35_res_1_Celsius, adc_res_1_txt);
        ret = convert_short_to_string(lm35_res_2_Celsius, adc_res_2_txt);
        
        ret = lcd_4bit_send_string_pos(&lcd_1,2, 8, adc_res_1_txt);
        ret = lcd_4bit_send_string_pos(&lcd_1,3, 8, adc_res_2_txt);
        
        if (lm35_res_1_Celsius > 20 ){
            ret = dc_motor_move_right(&motor_1);
        }
        else{
            ret = dc_motor_stop(&motor_1);
        }
        if (lm35_res_2_Celsius > 25 ){
            ret = dc_motor_move_left(&motor_2);
        }
        else{
            ret = dc_motor_stop(&motor_2);
        }
    }

    return (EXIT_SUCCESS);
}
void Application (void)
{
    ret = ADC_Init(&adc_1);
    ret = lcd_4bit_initialize(&lcd_1);
    ret = dc_motor_initialize(&motor_1);
    ret = dc_motor_initialize(&motor_2);
    ecu_layer_initialize();
}
void ADC_DefaultInterruptHandler(void){
    if (0 == ADC_Req){
        ret = ADC_GetConversionResult (&adc_1, &res_1);
        ADC_Req = 1;
    }
    else if (1 == ADC_Req){
        ret = ADC_GetConversionResult (&adc_1, &res_2);
        ADC_Req = 0;
    }
    else { /* Nothing */ }
}
