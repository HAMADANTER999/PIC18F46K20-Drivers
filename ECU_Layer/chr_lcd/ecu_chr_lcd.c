/* 
 * File:   ecu_chr_lcd.c
 * Author: anter
 *
 * Created on August 18, 2024, 2:30 PM
 */

#include "ecu_chr_lcd.h"

static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command);
static Std_ReturnType lcd_send_4bits_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_send_8bits_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 coulmn);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 coulmn);

/**
 * @brief initialize the lcd with 4 bit configurations
 * @param lcd pointer to the LCD configurations
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
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
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2LINE);
        ret = lcd_4bit_send_command(lcd, _LCD_DDRAM_START);
        
    }
    return ret;
}

/**
 * @brief send command to 4 bit lcd to execute
 * @param lcd pointer to the LCD configurations
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        
        ret = lcd_send_4bits(lcd, (command >> 4));
        ret = lcd_send_4bits_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, command);
        ret = lcd_send_4bits_enable_signal(lcd);
        
    }
    return ret;
}
/**
 * @brief send character to the lcd to display as data on the screen
 * @param lcd pointer to the LCD configurations
 * @param data the data we need to send to the LCD
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        
        ret = lcd_send_4bits(lcd, (data >> 4));
        ret = lcd_send_4bits_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, data);
        ret = lcd_send_4bits_enable_signal(lcd);
    }
    return ret;
}
/**
 * @brief send character to the lcd to display as data on the screen with position
 * @param lcd pointer to the LCD configurations
 * @param row
 * @param coulmn
 * @param data the data we need to send to the LCD
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
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
        ret = lcd_4bit_set_cursor(lcd, row, coulmn);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret;
}
/**
 * @brief send string to the lcd to display as data on the screen 
 * @param lcd pointer to the LCD configurations
 * @param str
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd || NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while (*str)
        {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
            
    }
    return ret;
}
/**
 * @brief send string to the lcd to display as data on the screen woth position
 * @param lcd pointer to the LCD configurations
 * @param row
 * @param coulmn
 * @param str
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
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
        ret = lcd_4bit_set_cursor(lcd, row, coulmn);
        while (*str)
        {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}
/**
 * @brief send custom charater to the lcd to display as data on the screen
 * @param lcd pointer to the LCD configurations
 * @param row
 * @param coulmn
 * @param str
 * @param _chr
 * @param mem_pos
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 coulmn, 
                                         const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for (lcd_counter = ZERO_INIT ; lcd_counter <= 7 ; lcd_counter++)
        {
            ret = lcd_4bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, coulmn, mem_pos);
    }
    return ret;
}

/**
 * @brief initialize the lcd with 8 bit configurations
 * @param lcd pointer to the LCD configurations
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
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
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        ret = lcd_8bit_send_command(lcd, _LCD_DDRAM_START);
    }
    return ret;
}
/**
 * @brief send command to 8 bit lcd to execute
 * @param lcd pointer to the LCD configurations
 * @param commad the command that we need to send to the LCD
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter = ZERO_INIT;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for (l_pin_counter = ZERO_INIT ; l_pin_counter<8 ; l_pin_counter++)
        {
          ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), ((command >> l_pin_counter) & (uint8)0x01));
        }
        lcd_send_8bits_enable_signal(lcd);
    }
    return ret;
}
/**
 * @brief send character to the lcd to display as data on the screen
 * @param lcd pointer to the LCD configurations
 * @param data the data we need to send to the LCD
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */    
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter = ZERO_INIT;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for (l_pin_counter = ZERO_INIT ; l_pin_counter<8 ; l_pin_counter++)
        {
          ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), ((data >> l_pin_counter) & (uint8)0x01));
        }
        lcd_send_8bits_enable_signal(lcd);
    }
    return ret;
}
/**
 * @brief send character to the lcd to display as data on the screen with position
 * @param lcd pointer to the LCD configurations
 * @param row
 * @param coulmn
 * @param data the data we need to send to the LCD
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
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
        ret = lcd_8bit_set_cursor(lcd, row, coulmn);
        ret = lcd_8bit_send_char_data(lcd, data);
    }
    return ret;
}
/**
 * @brief send string to the lcd to display as data on the screen
 * @param lcd pointer to the LCD configurations
 * @param str
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd || NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while (*str)
        {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}
/**
 * @brief send string to the lcd to display as data on the screen with position
 * @param lcd pointer to the LCD configurations
 * @param row
 * @param coulmn
 * @param str
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
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
        ret = lcd_8bit_set_cursor(lcd, row, coulmn);
        while (*str)
        {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}
/**
 * @brief send custom character to the lcd to display as data on the screen
 * @param lcd pointer to the LCD configurations
 * @param row
 * @param coulmn
 * @param str
 * @param _chr
 * @param mem_pos
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 coulmn,
                                         const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for (lcd_counter = ZERO_INIT ; lcd_counter <= 7 ; lcd_counter++)
        {
            ret = lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, coulmn, mem_pos);
    }
    return ret;
}
/**
 * @brief coverts byte to string
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType convert_byte_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    uint8 Temp_String[4] = {0};
    uint8 DataCounter = 0;
    if (NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, ' ', 3);
        str[4] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while (Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter];
            DataCounter++;
        }
    }
    return ret;
}
/**
 * @brief converts short to string
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType convert_short_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if (NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while (Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter];
            DataCounter++;
        }
    }
    return ret;
}
/**
 * @brief convert intger to string 
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
Std_ReturnType convert_int_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    uint8 Temp_String[11] = {0};
    uint8 DataCounter = 0;
    if (NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, ' ', 10);
        str[11] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while (Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter];
            DataCounter++;
        }
    }
    return ret;
}

/**
 * @brief send 4 bits command to lcd one by one
 * @param lcd pointer to the LCD configurations
 * @param _data_commad the data where we need to send
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), ((_data_command >> 0) & (uint8)0x01));
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), ((_data_command >> 1) & (uint8)0x01));
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), ((_data_command >> 2) & (uint8)0x01));
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), ((_data_command >> 3) & (uint8)0x01));
    }
    return ret;
}

/**
 * @brief enable the enable pin to send data from buffer to registers
 * @param lcd pointer to the LCD configurations
 * @return Status of the function
 *          (E_OK)       : the function done successfully 
 *          (E_NOT_OK)   : the function has issue to perform this action
 */
static Std_ReturnType lcd_send_4bits_enable_signal(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @return 
 */
static Std_ReturnType lcd_send_8bits_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if (NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}


static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 coulmn){
    Std_ReturnType
    ret = E_OK;
    if (lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        coulmn--; 
        switch(row)
        {
            case ROW1 : lcd_8bit_send_command(lcd, (0x80 + coulmn)); break;
            case ROW2 : lcd_8bit_send_command(lcd, (0xc0 + coulmn)); break;
            case ROW3 : lcd_8bit_send_command(lcd, (0x94 + coulmn)); break;
            case ROW4 : lcd_8bit_send_command(lcd, (0xd4 + coulmn)); break;
            default : /* Nothing */ break;
        }
    }
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 coulmn){
    Std_ReturnType
    ret = E_OK;
    if (lcd == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        coulmn--; 
        switch(row)
        {
            case ROW1 : lcd_4bit_send_command(lcd, (0x80 + coulmn)); break;
            case ROW2 : lcd_4bit_send_command(lcd, (0xc0 + coulmn)); break;
            case ROW3 : lcd_4bit_send_command(lcd, (0x94 + coulmn)); break;
            case ROW4 : lcd_4bit_send_command(lcd, (0xd4 + coulmn)); break;
            default : /* Nothing */ break;
        }
    }
    return ret;
}