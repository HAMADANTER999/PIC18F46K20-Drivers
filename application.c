/* 
 * File:   application.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "application.h"

timer3_t timer3_obj;
ccp_t ccp_obj;

volatile uint8 CCP1_Callback_Flag = 0;

void CCP1_DefaultInterruptHandler(void){
    Std_ReturnType ret = E_NOT_OK;
    
    CCP1_Callback_Flag++;
    
    ret = Timer3_Write_Value(&timer3_obj, 0);
    
    if(CCP1_Callback_Flag == 1){
        /* Load a count for generating a duty cycle = 25% */
        ret = CCP_Compare_Mode_Set_Value(&ccp_obj, 12500); 
        /* On compare match, force CCPx pin low (CCPxIF bit is set) */
        CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH); 
    }
    else if(CCP1_Callback_Flag == 2){
        /* Load a count for generating a duty cycle = 75% */
        ret = CCP_Compare_Mode_Set_Value(&ccp_obj, 37500); 
        /* On compare match, force CCPx pin high (CCPxIF bit is set) */
        CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW); 
        CCP1_Callback_Flag = 0;
    }
}

int main() { 
    Std_ReturnType ret = E_NOT_OK;
    
    //application_intialize();

    ccp_obj.CCP1_InterruptHandler = CCP1_DefaultInterruptHandler;
    ccp_obj.ccp_inst = CCP1_INST;
    ccp_obj.ccp_mode = CCP_COMPARE_MODE_SELECTED;
    ccp_obj.ccp_mode_variant = CCP_COMPARE_MODE_SET_PIN_LOW; 
    ccp_obj.ccp_mode_variant = CCP1_CCP2_TIMER3;
    ccp_obj.pin.port = PORTC_INDEX;
    ccp_obj.pin.pin = GPIO_PIN2;
    ccp_obj.pin.direction = GPIO_DIRECTION_OUTPUT;
    
    /* Load a count for generating a duty cycle = 25% */
    ret = CCP_Compare_Mode_Set_Value(&ccp_obj, 37500); 
    
    ret = CCP_Init(&ccp_obj);
    
    timer3_obj.TMR3_InterruptHandler = NULL;
    timer3_obj.timer3_mode = TIMER3_TIMER_MODE;
    timer3_obj.priority = INTERRUPT_LOW_PRIORITY;
    timer3_obj.timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_1;
    timer3_obj.timer3_preloaded_value = 0;
    timer3_obj.timer3_reg_wr_mode = TIMER3_RW_REG_16BIT_MODE;
    ret = Timer3_Init(&timer3_obj);
    
    while(1){    
        
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_initialize();
}


