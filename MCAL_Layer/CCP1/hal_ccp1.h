/* 
 * File:   hal_ccp1.h
 * Author: anter
 *
 * Created on September 19, 2024, 12:32 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* Section : includes*/
#include "xc.h"
#include "hal_ccp1_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupts.h"

/* Section : Macro Declarations*/

/* CCP1 Module Mode Select */
#define CCP1_MODULE_DISABLE                     ((uint8)0X00)
#define CCP1_CAPTURE_MODE_1_FALLING_EDGE        ((uint8)0X04)
#define CCP1_CAPTURE_MODE_1_RISING_EDGE         ((uint8)0X05)
#define CCP1_CAPTURE_MODE_4_RISING_EDGE         ((uint8)0X06)
#define CCP1_CAPTURE_MODE_16_RISING_EDGE        ((uint8)0X07)
#define CCP1_COMPARE_MODE_SET_PIN_LOW           ((uint8)0X08)
#define CCP1_COMPARE_MODE_SET_PIN_HIGH          ((uint8)0X09)
#define CCP1_COMPARE_MODE_TOGGLE_ON_MATCH       ((uint8)0X02)
#define CCP1_COMPARE_MODE_GEN_SW_INTERRUPT      ((uint8)0X0A)
#define CCP1_COMPARE_MODE_GEN_EVENT             ((uint8)0X0B)
#define CCP1_PWM_MODE                           ((uint8)0X0C)

/* CCP1 Capture Mode State */
#define CCP1_CAPTURE_NOT_READY                  0X00
#define CCP1_CAPTURE_READY                      0X01

/* CCP1 Compare Mode State */
#define CCP1_COMPARE_NOT_READY                  0X00
#define CCP1_COMPARE_READY                      0X01



/* Section : Macro Function Declarations*/

#define CCP1_SET_MODE(_CONFIG)      (CCP1CONbits.CCP1M = _CONFIG)
 

/* Section : Data type Declarations*/

/*
 * @Summary Defines the values to select the ccp1 main mode 
 */
typedef enum {
    CCP1_CAPTURE_MODE_SELECTED = 0, /*  select CCP1 Capture Mode */
    CCP1_COMPARE_MODE_SELECTED,     /*  select CCP1 Compare Mode */
    CCP1_PWM_MODE_SELECTED,         /*  select CCP1 PWM Mode */
}ccp1_mode_t;

/*
 * @Summary Defines the values to convert from 16bit to two 8bit and vice verse
 * @Description Used to get 8bit values from 16bit also two 8bit value are combine to get 16bit
 */

typedef union {
    typedef struct {
        uint8 ccpr1_low;   /*CCP1 Low register */ 
        uint8 ccpr1_high;  /*CCP1 High register */
    };
    typedef struct {
        uint16 ccpr1_16bit; /* Read CCP1 as 16bit value */
    };
    
}CCP1_PREIOD_REG_T;

/*
 * @Summary CCP1 Module Configurations
 * @Description this data is used to describe the module initialization configuration
 * 
 */
typedef struct {
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
    void (*CCP1_InterruptHandler)(void); /* call back used for all CCP1 modes */
    interrupt_priority_cfg priority; /* Configure the CCP1 mode interrupt */
#endif
#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED)
  uint32 PWM_Frequency; /* CCP1 PWM Frequency */
#endif
  ccp1_mode_t ccp1_mode; /* CCP1 Main module */
  uint8 ccp1_mode_variant; /* CCP1 Select mode variant */

}ccp1_t;

/* Section : Function Declarations*/
Std_ReturnType CCP1_Init(const ccp1_t * _ccp_obj);
Std_ReturnType CCP1_DeInit(const ccp1_t * _ccp_obj);

#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP1_IsCaptureDataReady(uint8 *_capture_status);
Std_ReturnType CCP1_Capture_Mode_Read_value(uint16 *capture_value);
#endif 

#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP1_IsCompareComplete(uint8 *_compare_status);
Std_ReturnType CCP1_Compare_Mode_Set_Value(uint16 compare_value);
#endif 

#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP1_PWM1_Set_Duty(const uint16 _duty);
Std_ReturnType CCP1_PWM1_Start(void);
Std_ReturnType CCP1_PWM1_Stop(void);
#endif 

#endif	/* HAL_CCP1_H */

