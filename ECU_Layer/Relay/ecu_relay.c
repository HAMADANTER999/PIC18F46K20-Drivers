/* 
 * File:   ecu_relay.c
 * Author: anter
 *
 * Created on August 13, 2024, 3:48 PM
 */

#include "ecu_relay.h"

/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_initialize(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if (relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    
    return ret;
}

/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_turn_on(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if (relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    
    return ret;
}

/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_turn_off(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if (relay == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    
    return ret;
}