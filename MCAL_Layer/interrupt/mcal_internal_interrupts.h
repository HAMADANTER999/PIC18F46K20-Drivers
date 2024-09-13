/* 
 * File:   mcal_internal_interrupts.h
 * Author: anter
 *
 * Created on August 23, 2024, 1:03 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section : includes*/
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations*/

/* Section : Macro Function Declarations*/
/* This routine clears the interrupt enable for the ADC Module*/
#ifdef ADC_INTERRUPT_FEATURE_ENABLE
#define ADC_InterruptDisable()         (PIE1bits.ADIE = 0)
/* This routine sets the interrupt enable for the ADC Module */
#define ADC_InterruptEnable()          (PIE1bits.ADIE = 1)
/* This routine clears the interrupt flag for the ADC Module */
#define ADC_InterruptFlagClear()       (PIR1bits.ADIF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
/* This routine set the ADC Module Interrupt Priority to be High priority */
#define ADC_HighPrioritySet()           (IPR1bits.ADIP = 1)
/* This routine set the ADC Module Interrupt Priority to be Low priority */
#define ADC_LowPrioritySet()            (IPR1bits.ADIP = 0)
#endif
#endif
/* Section : Data type Declarations*/

/* Section : Function Declarations*/


#endif	/* MCAL_INTERNAL_INTERRUPTS_H */

