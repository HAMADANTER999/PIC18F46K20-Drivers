/* 
 * File:   mcal_interrupt_config.h
 * Author: anter
 *
 * Created on August 23, 2024, 1:08 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section : includes*/
#include "xc.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"
/* Section : Macro Declarations*/
#define INTERRUPT_ENABLE              1
#define INTERRUPT_DISABLE             0
#define INTERRUPT_OCCUR               1
#define INTERRUPT_NOT_OCCUR           0
#define INTERRUPT_PRIORITY_ENABLE     1
#define INTERRUPT__PRIORITY_DISABLE   0

/* Section : Macro Function Declarations*/
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
/* this macro will enable priority levels on interrupts */
#define INTERRUPT_PriorityLevelsEnable()       (RCONbits.IPEN = 1)
/* this macro will disable priority levels on interrupts */
#define INTERRUPT_PriorityLevelsDisable()      (RCONbits.IPEN = 0)
/* this macro will enable high priority global interrupts */
#define INTERRUPT_GlobalInterruprHighEnable()  (INTCONbits.GIEH = 1)
/* this macro will disable high priority global interrupts */
#define INTERRUPT_GlobalInterruprHighDisable() (INTCONbits.GIEH = 0)
/* this macro will enable low priority global interrupts */
#define INTERRUPT_GlobalInterruprLowEnable()   (INTCONbits.GIEL = 1)
/* this macro will disable low priority global interrupts */
#define INTERRUPT_GlobalInterruprLowDisable()  (INTCONbits.GIEL = 0)
/* this macro will enable peripheral interrupts */
#else
/* this macro will enable global interrupts */
#define INTERRUPT_GlobalInterruprEnable()      (INTCONbits.GIE = 1)
/* this macro will disable global interrupts */
#define INTERRUPT_GlobalInterruprDisable()     (INTCONbits.GIE = 0)
/* this macro will enable peripheral interrupts */
#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)
/* this macro will disable peripheral interrupts */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

#endif


/* Section : Data type Declarations*/
typedef enum {
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY,
}interrupt_priority_cfg;

/* Section : Function Declarations*/

#endif	/* MCAL_INTERRUPT_CONFIG_H */

