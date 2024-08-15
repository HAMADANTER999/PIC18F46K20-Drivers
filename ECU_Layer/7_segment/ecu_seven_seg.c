/* 
 * File:   ecu_seven_seg.c
 * Author: anter
 *
 * Created on August 15, 2024, 7:07 PM
 */

#include "ecu_seven_seg.h"

Std_ReturnType seven_segment_intialize(const segment_t *seg){
    Std_ReturnType ret = E_OK;
    if (seg == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
}
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number){
    Std_ReturnType ret = E_OK;
    if ((seg == NULL) || (number > 9))
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
}