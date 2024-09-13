/* 
 * File:   hal_adc.h
 * Author: anter
 *
 * Created on August 30, 2024, 10:56 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Section : includes*/
#include "xc.h"
#include "hal_adc_cfg.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupts.h"
/* Section : Macro Declarations*/

/**
 * @brief Analog-To-Digital port Configuration Control 
 * @note When ADC_AN4_ANALOG_FUNCTIONALITY is Configured, this mean 
 *       AN4,AN3,AN2,AN1,AN0 are analog functionality
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY     0X0E
#define ADC_AN1_ANALOG_FUNCTIONALITY     0X0D
#define ADC_AN2_ANALOG_FUNCTIONALITY     0X0C
#define ADC_AN3_ANALOG_FUNCTIONALITY     0X0B
#define ADC_AN4_ANALOG_FUNCTIONALITY     0X0A
#define ADC_AN5_ANALOG_FUNCTIONALITY     0X09
#define ADC_AN6_ANALOG_FUNCTIONALITY     0X08
#define ADC_AN7_ANALOG_FUNCTIONALITY     0X07
#define ADC_AN8_ANALOG_FUNCTIONALITY     0X06
#define ADC_AN9_ANALOG_FUNCTIONALITY     0X05
#define ADC_AN10_ANALOG_FUNCTIONALITY    0X04
#define ADC_AN11_ANALOG_FUNCTIONALITY    0X03
#define ADC_AN12_ANALOG_FUNCTIONALITY    0X02
#define ADC_ALL_ANALOG_FUNCTIONALITY     0X00
#define ADC_ALL_DIGITAL_FUNCTIONALITY    0X0F

#define ADC_RESULT_RIGHT                 0X01U
#define ADC_RESULT_LEFT                  0X00U

#define ADC_VOLTAGE_REFERENCE_ENALBE     0X01U
#define ADC_VOLTAGE_REFERENCE_DISALBE    0X00U

#define ADC_CONVERSION_COMPLETED   1
#define ADC_CONVERSION_INPROGRESS  0

/* Section : Macro Function Declarations*/

/* A/D Conversion Status : A/D conversion in progress / A/D Idle  */
#define ADC_CONVERSION_STATUS()    (ADCON0bits.GO_nDONE)

/**
 * @brief  start Analog-To-Digital Convertion
 */
#define ADC_START_CONVERSION()     (ADCON0bits.GO_nDONE = 1)

/**
 * @brief Analog-To-Digital Control
 * @note ADC_CONVERTER_ENABLE() : Enable Analog-To-Digital
 *       ADC_CONVERTER_DISABLE(): Disable Analog-To-Digital
 */
#define ADC_CONVERTER_ENABLE()     (ADCON0bits.ADON = 1) 
#define ADC_CONVERTER_DISABLE()    (ADCON0bits.ADON = 0) 

/**
 * @brief Voltage reference enable 
 * @note ADC_ENALBE_VOLTAGE_REFERENCE() : Voltage reference is VREF- & VREF+
 *       ADC_DIALBE_VOLTAGE_REFERENCE() : Voltage reference is VSS & VDD
 **/
#define ADC_ENALBE_VOLTAGE_REFERENCE()  do{ADCON1bits.VCFG1 = 1;\
                                           ADCON1bits.VCFG0 = 1;\
                                        }while(0)

#define ADC_DIALBE_VOLTAGE_REFERENCE()  do{ADCON1bits.VCFG1 = 0;\
                                           ADCON1bits.VCFG0 = 0;\
                                        }while(0)


/**
 * @brief Analog-To-Digital port Configuration Control 
 * @note Example : ADC_ANALOG_TO_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY)  
 *       When ADC_AN4_ANALOG_FUNCTIONALITY is Configured, this mean 
 *       AN4,AN3,AN2,AN1,AN0 are analog functionality
 * @ref  Analog-To-Digital port Configuration Control
 */ 
#define ADC_ANALOG_TO_DIGITAL_PORT_CONFIG(_CONFIG)  (ADCON1bits.PCFG = _CONFIG) /* MAY CAUSE ERROR */

/**
 * @brief  A/D Result Format Select bit
 */
#define ADC_RESULT_RIGHT_FORMAT()      (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()       (ADCON2bits.ADFM = 0)

/* Section : Data type Declarations*/

/**
 * @brief Analog select channel
 */
typedef enum {
   ADC_CHANNEL_AN0 = 0,
   ADC_CHANNEL_AN1,
   ADC_CHANNEL_AN2,
   ADC_CHANNEL_AN3,
   ADC_CHANNEL_AN4,
   ADC_CHANNEL_AN5,
   ADC_CHANNEL_AN6,
   ADC_CHANNEL_AN7,
   ADC_CHANNEL_AN8,
   ADC_CHANNEL_AN9,
   ADC_CHANNEL_AN10,
   ADC_CHANNEL_AN11,        
   ADC_CHANNEL_AN12,        
}adc_channel_select_t;


/**
 *@brief  A/D Acquisition Time Select bits
 *@note acquisition time or (sampling time) is the time required for the ADC to 
 *      capture the input voltage during sampling
 * @note acquisition time of a successive Approximation Register (SAR) ADC is the amount
 *       of time required to charge the holding capacitor (CHOLD) on the front end of an ADC
 */
typedef enum {
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
}adc_acquisition_time_t;

/**
 *@brief A/D Conversion Clock Select bits
 * @note  If the A/D FRC clock source is selected, a delay of one TCY (instruction cycle) 
 *        is added before the A/D clock starts
 * @note This allows the SLEEP instruction to be executed before starting a conversion.
 */
typedef enum {
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64,       
}adc_conversion_clock_t;

typedef struct {
#ifdef ADC_INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler) (void);
    interrupt_priority_cfg priority;
#endif 
    adc_acquisition_time_t Acquisition_time;   /* @ref adc_acquisition_time_t */
    adc_conversion_clock_t convertion_clock;   /* @ref adc_conversion_clock_t */
    adc_channel_select_t adc_channel;          /* @ref adc_channel_select_t */
    uint8 voltage_reference : 1;               /* Voltage reference configuration */
    uint8 result_format : 1;                   /* A/D result format select */
    uint8 ADC_Reserved : 6;
}adc_conf_t;

typedef uint16 adc_result_t;
/* Section : Function Declarations*/

Std_ReturnType ADC_Init(const adc_conf_t *_adc);
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc);
Std_ReturnType ADC_SelectChannel (const adc_conf_t *_adc, adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion (const adc_conf_t *_adc);
Std_ReturnType ADC_IsConversionDone (const adc_conf_t *_adc, uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult (const adc_conf_t *_adc, adc_result_t *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking (const adc_conf_t *_adc, adc_channel_select_t channel,
                                  adc_result_t *conversion_result);
Std_ReturnType ADC_GetConversion_Interrupt (const adc_conf_t *_adc, adc_channel_select_t channel);

#endif	/* HAL_ADC_H */

