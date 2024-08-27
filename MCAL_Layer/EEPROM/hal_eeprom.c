/* 
 * File:   hal_eeprom.c
 * Author: anter
 *
 * Created on August 27, 2024, 8:16 PM
 */

#include "hal_eeprom.h"

Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
    Std_ReturnType ret = E_OK;
    /* Read the interrupt status " Enable or Disable" */
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    /* Update the Address Register*/
    EEADRH = (uint8)((bAdd >> 8) & 0x03);
    EEADR = (uint8) (bAdd & 0xFF);
    /* Update the Data register */
    EEDATA = bData;
    /* select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    /* Allows write cycles to flash program/data EEPROM */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    /* Disable all interrupts " General Interrupt" */
    INTERRUPT_GlobalInterruprDisable();
    /* Write the required sequence : 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiates a data EEPROM  erase/write cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /* Wait for write to complete */
    while (EECON1bits.WR);
    /* Inhibits write cycles to flash program/data EEPROM */
    EECON1bits.WREN = INHIBITS_WRITE_CYCLES_FLASH_EEPROM;
    /* Restore the interrupt status "Enabled or Disabled" */
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
    Std_ReturnType ret = E_OK;
    if (NULL == bData)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Update the Address Registers */
        EEADRH = (uint8)((bAdd >> 8) & 0x03);
        EEADR = (uint8) (bAdd & 0xFF);
        /* Select Access Data EEPROM Memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        /* initiates a data EEPROM read cycle */
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP();
        NOP();
        /* Return data */
        *bData = EEDATA;
    }
    return ret;
}
