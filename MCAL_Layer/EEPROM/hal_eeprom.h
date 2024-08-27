/* 
 * File:   hal_eeprom.h
 * Author: anter
 *
 * Created on August 27, 2024, 8:16 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* Section : includes*/

#include "xc.h"
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupts.h"

/* Section : Macro Declarations*/
/*  Flash Program or Data EEPROM Memory Select bit */
#define ACCESS_FLASH_PROGRAM_MEMORY           1
#define ACCESS_EEPROM_PROGRAM_MEMORY          0
/* Flash Program/Data EEPROM or Configuration Select bit */
#define ACCESS_CONFIG_REGISTERS               1
#define ACCESS_FLASH_EEPROM_MEMORY            0
/* Flash Program/Data EEPROM Error Flag bit */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM       1
#define INHIBITS_WRITE_CYCLES_FLASH_EEPROM    0
/* Write control */
#define INITIATE_DATA_EEPROM_WRITE_ERASE      1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED     0
/* Read control */
#define INITIATE_DATA_EEPROM_READ             1




/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/

/* Section : Function Declarations*/

Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);



#endif	/* HAL_EEPROM_H */

