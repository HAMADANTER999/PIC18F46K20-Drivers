/* 
 * File:   ecu_keypad_cfg.c
 * Author: anter
 *
 * Created on August 16, 2024, 1:34 PM
 */

#include "ecu_keypad.h"

/**
 * @brief 
 * @param _keypad_obj
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj){
    Std_ReturnType ret = E_OK;
    if (_keypad_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    
    return ret;
    
}

/**
 * @brief 
 * @param _keypad_obj
 * @param value
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value){
    Std_ReturnType ret = E_OK;
    if ((_keypad_obj == NULL) || (value == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    
    return ret;
    
}

