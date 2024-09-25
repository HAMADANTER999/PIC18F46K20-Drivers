/* 
 * File:   hal_usart.c
 * Author: anter
 *
 * Created on September 25, 2024, 12:00 AM
 */

#include "hal_usart.h"


Std_ReturnType EUSART_Init(const usart_t *_eusart){
    Std_ReturnType ret = E_OK;
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else {
        
    }
    return ret;
}
Std_ReturnType EUSART_DeInit(const usart_t *_eusart){
    Std_ReturnType ret = E_OK;
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else {
        
    }
    return ret;
}
Std_ReturnType EUSART_ReadByteBlocking(const usart_t *_eusart, uint8 * _data){
    Std_ReturnType ret = E_OK;
    if((NULL == _eusart) || (NULL == _data)){
        ret = E_NOT_OK;
    }
    else {
        
    }
    return ret;
}
Std_ReturnType EUSART_WriteByteBlocking(const usart_t *_eusart, uint8 _data){
    Std_ReturnType ret = E_OK;
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    else {
        
    }
    return ret;
}