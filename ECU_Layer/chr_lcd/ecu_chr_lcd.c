/* 
 * File:   ecu_chr_lcd.c
 * Author: anter
 *
 * Created on August 18, 2024, 2:30 PM
 */

#include "ecu_chr_lcd.h"

/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 l_data_pin_counter = ZERO_INIT;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for (l_data_pin_counter = ZERO_INIT ; l_data_pin_counter<4 ; l_data_pin_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_pin_counter]));
        }
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 commad){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
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
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
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
 * @param lcd
 * @param row
 * @param coulmn
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row, uint8 coulmn,
                                           uint8 data){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
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
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd || NULL == str)
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
 * @param lcd
 * @param row
 * @param coulmn
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 coulmn, 
                                        uint8 *str){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd || NULL == str)
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
 * @param lcd
 * @param row
 * @param coulmn
 * @param str
 * @param _chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 coulmn, 
                                         uint8 *str,const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd || NULL == str)
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
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 l_data_pin_counter = ZERO_INIT;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for (l_data_pin_counter = ZERO_INIT ; l_data_pin_counter<8 ; l_data_pin_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_pin_counter]));
        }
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param commad
 * @return 
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 commad){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
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
 * @param lcd
 * @param data
 * @return 
 */    
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
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
 * @param lcd
 * @param row
 * @param coulmn
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row, uint8 coulmn,
                                           uint8 data){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
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
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd || NULL == str)
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
 * @param lcd
 * @param row
 * @param coulmn
 * @param str
 * @return 
 */    
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 coulmn,
                                        uint8 *str){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd || NULL == str)
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
 * @param lcd
 * @param row
 * @param coulmn
 * @param str
 * @param _chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 coulmn,
                                         uint8 *str,const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd || NULL == str)
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
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_byte_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if (NULL == str)
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
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_short_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if (NULL == str)
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
 * @param value
 * @param str
 * @return 
 */
Std_ReturnType convert_int_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if (NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
    }
    return ret;
}