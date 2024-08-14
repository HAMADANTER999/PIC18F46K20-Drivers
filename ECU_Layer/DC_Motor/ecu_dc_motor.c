/* 
 * File:   ecu_dc_motor.c
 * Author: anter
 *
 * Created on August 13, 2024, 10:27 PM
 */

#include "ecu_dc_motor.h"

/**
 * @brief Initialize the assigned pin to be OUTPUT and dc_motor module
 * @param _dc_motor pointer to the dc motor module configurations
 * @return status of the function 
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType dc_motor_initialize(dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if (_dc_motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        gpio_pin_intialize(&(_dc_motor->dc_motor[MOTOR_INDEX_PIN1]));
        gpio_pin_intialize(&(_dc_motor->dc_motor[MOTOR_INDEX_PIN2]));
        
    }
    return ret;
}

/**
 * @brief move dc motor right
 * @param _dc_motor pointer to the dc motor module configurations
 * @return status of the function 
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right(dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if (_dc_motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor[MOTOR_INDEX_PIN1]), GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor[MOTOR_INDEX_PIN2]), GPIO_LOW);
    }
    return ret;
}

/**
 * @brief move dc motor left
 * @param _dc_motor pointer to the dc motor module configurations
 * @return status of the function 
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left(dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if (_dc_motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor[MOTOR_INDEX_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor[MOTOR_INDEX_PIN2]), GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief stop dc motor
 * @param _dc_motor pointer to the dc motor module configurations
 * @return status of the function 
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if (_dc_motor == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor[MOTOR_INDEX_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor[MOTOR_INDEX_PIN2]), GPIO_LOW);
    }
    return ret;
}