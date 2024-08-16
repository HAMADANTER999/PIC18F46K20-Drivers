/* 
 * File:   ecu_keypad_cfg.c
 * Author: anter
 *
 * Created on August 16, 2024, 1:34 PM
 */

#include "ecu_keypad.h"

static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
                                                        {'7', '8', '9', '/'},
                                                        {'4', '5', '6', '7'},
                                                        {'1', '2', '3', '4'},
                                                        {'#', '0', '=', '+'}
                                                        };

/**
 * @brief initialize keypad module
 * @param _keypad_obj
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj){
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = ZERO_INIT, columns_counter = ZERO_INIT;
    if (_keypad_obj == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for (rows_counter = ZERO_INIT ; rows_counter < ECU_KEYPAD_ROWS ; rows_counter++)
        {
            gpio_pin_intialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
        }
        for (columns_counter = ZERO_INIT ; columns_counter < ECU_KEYPAD_COLUMNS ; columns_counter++)
        {
            gpio_pin_direction_intialize(&(_keypad_obj->keypad_row_pins[columns_counter]));
        }
        
    }
    
    return ret;
    
}

/**
 * @brief scanning keypad algorithm to get value pressed
 * @param _keypad_obj
 * @param value pointer to the value being pressed
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value){
    Std_ReturnType ret = E_OK;
    uint8 l_row_counter = ZERO_INIT, l_counter = ZERO_INIT, l_columns = ZERO_INIT, l_column_counter;
    uint8 column_logic = ZERO_INIT;
    if ((_keypad_obj == NULL) || (value == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {
        for (l_row_counter = ZERO_INIT ; l_row_counter < ECU_KEYPAD_ROWS ; l_row_counter++)
        {
            for (l_counter = ZERO_INIT ; l_counter < ECU_KEYPAD_ROWS ; l_counter++)
            {
                ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]), GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_row_counter]), GPIO_HIGH);
            for (l_column_counter = ZERO_INIT ; l_column_counter < ECU_KEYPAD_COLUMNS ; l_column_counter++)
            {
                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[l_column_counter]), &column_logic);
                if (column_logic == GPIO_HIGH)
                {
                    *value = btn_values[l_row_counter][l_column_counter];
                }
            }

        }
        
    }
    
    return ret;
    
}

