/* 
 * File:   ecu_button.c
 * Author: anter
 *
 * Created on August 12, 2024, 12:15 PM
 */

#include "ecu_button.h"

/**
 * @brief initialize pin to the INPUT for button connected
 * @param btn is pointer to the button configurations
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */

Std_ReturnType button_initialize(const button_t *btn){
    Std_ReturnType ret = E_OK;
    if (btn == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
    
}

/**
 * @brief read the state of the button
 * @param btn is pointer to the button configurations
 * @param btn_state
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
    Std_ReturnType ret = E_OK;
    if (btn == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
    
}