/* 
 * File:   ecu_relay.c
 * Author: anter
 *
 * Created on August 13, 2024, 3:48 PM
 */

#include "ecu_relay.h"

/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the relay off
 * @param relay pointer to the relay module configurations
 * @return status of the function 
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType relay_initialize(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if (relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status,
        };
        
        gpio_pin_intialize(&pin_obj);
        
    }
    
    return ret;
}

/**
 * @brief turn the relay on
 * @param relay pointer to the relay module configurations
 * @return status of the function 
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType relay_turn_on(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if (relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status,
        };
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    
    return ret;
}

/**
 * @brief turn the relay off
 * @param relay pointer to the relay module configurations
 * @return status of the function 
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType relay_turn_off(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if (relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
         pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status,
        };
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
        
    }
    
    return ret;
}