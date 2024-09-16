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
/*=======================================ADC Interrupt Module ==============================*/
#ifdef ADC_INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the ADC Module*/
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

/*=======================================TIMER0 Interrupt Module ==============================*/
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the TIMER0 Module*/
#define TIMER0_InterruptDisable()         (INTCONbits.TMR0IE = 0)
/* This routine sets the interrupt enable for the TIMER0 Module */
#define TIMER0_InterruptEnable()          (INTCONbits.TMR0IE = 1)
/* This routine clears the interrupt flag for the TIMER0 Module */
#define TIMER0_InterruptFlagClear()       (INTCONbits.TMR0IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
/* This routine set the TIMER0 Module Interrupt Priority to be High priority */
#define TIMER0_HighPrioritySet()           (INTCON2bits.TMR0IP = 1)
/* This routine set the TIMER0 Module Interrupt Priority to be Low priority */
#define TIMER0_LowPrioritySet()            (INTCON2bits.TMR0IP = 0)
#endif
#endif

/*=======================================TIMER1 Interrupt Module ==============================*/
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the TIMER1 Module*/
#define TIMER1_InterruptDisable()         (PIE1bits.TMR1IE = 0)
/* This routine sets the interrupt enable for the TIMER1 Module */
#define TIMER1_InterruptEnable()          (PIE1bits.TMR1IE = 1)
/* This routine clears the interrupt flag for the TIMER1 Module */
#define TIMER1_InterruptFlagClear()       (PIR1bits.TMR1IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
/* This routine set the TIMER1 Module Interrupt Priority to be High priority */
#define TIMER1_HighPrioritySet()           (IPR1bits.TMR1IP = 1)
/* This routine set the TIMER1 Module Interrupt Priority to be Low priority */
#define TIMER1_LowPrioritySet()            (IPR1bits.TMR1IP = 0)
#endif
#endif
/* Section : Data type Declarations*/

/* Section : Function Declarations*/


#endif	/* MCAL_INTERNAL_INTERRUPTS_H */

