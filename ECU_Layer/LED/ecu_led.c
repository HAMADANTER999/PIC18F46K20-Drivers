 /* 
 * File:   ecu_led.c
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */

#include "ecu_led.h"

/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the led off
 * @param led pointer to the led module configurations
 * @return status of the function 
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType ret = E_OK;
    if (led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
}

/**
 * @brief turn the led on
 * @param led pointer to the led module configurations
 * @return status of the function 
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK;
    if (led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
    
}

/**
 * @brief turn the led off
 * @param led pointer to the led module configurations
 * @return status of the function 
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret = E_OK;
    if (led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
    
}

/**
 * @brief toggle the led
 * @param led pointer to the led module configurations
 * @return status of the function 
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType led_turn_toggle(const led_t *led){
    Std_ReturnType ret = E_OK;
    if (led == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
    
}