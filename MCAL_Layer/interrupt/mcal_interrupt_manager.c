/* 
 * File:   mcal_interrupt_manager.c
 * Author: anter
 *
 * Created on August 23, 2024, 1:07 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
void __interrupt() InterruptManagerHigh(void){
    if ((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR))
    {
        INT0_ISR();
    }
    else { /* Nothing */}
    if ((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR))
    {
        INT2_ISR();
    }
    else { /* Nothing */}
}

void __interrupt(low_priority) InterruptManagerLow(void){
    if ((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR))
    {
        INT1_ISR();
    }
    else { /* Nothing */}
}
#else

void __interrupt() InterruptManager(void){
    
    /* =====================PORTB INTx external interrupt start=========================*/
    if ((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR))
    {
        INT0_ISR();
    }
    else { /* Nothing */}
    if ((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR))
    {
        INT1_ISR();
    }
    else { /* Nothing */}
    if ((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR))
    {
        INT2_ISR();
    }
    else { /* Nothing */}
    /* =====================PORTB INTx external interrupt End=========================*/
    
    /* =====================PORTB On change external interrupt start=========================*/
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) &&
         (GPIO_HIGH == PORTBbits.RB4) && (1 == RB4_Flag))
    {
        RB4_Flag = 0;
        RB4_ISR(1);
    }
    else{ /* Nothing */ }
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
        (GPIO_LOW == PORTBbits.RB4) && (0 == RB4_Flag))
    {
        RB4_Flag = 1;
        RB4_ISR(0);
    }
    else{ /* Nothing */ }
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) &&
         (GPIO_HIGH == PORTBbits.RB5) && (1 == RB5_Flag))
    {
        RB5_Flag = 0;
        RB5_ISR(1);
    }
    else{ /* Nothing */ }
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
        (GPIO_LOW == PORTBbits.RB5) && (0 == RB5_Flag))
    {
        RB5_Flag = 1;
        RB5_ISR(0);
    }
    
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) &&
         (GPIO_HIGH == PORTBbits.RB6) && (1 == RB6_Flag))
    {
        RB6_Flag = 0;
        RB6_ISR(1);
    }
    else{ /* Nothing */ }
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
        (GPIO_LOW == PORTBbits.RB6) && (0 == RB6_Flag))
    {
        RB6_Flag = 1;
        RB6_ISR(0);
    }
    
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) &&
         (GPIO_HIGH == PORTBbits.RB7) && (1 == RB7_Flag))
    {
        RB7_Flag = 0;
        RB7_ISR(1);
    }
    else{ /* Nothing */ }
    if ((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
        (GPIO_LOW == PORTBbits.RB7) && (0 == RB7_Flag))
    {
        RB7_Flag = 1;
        RB7_ISR(0);
    }
    else{ /* Nothing */ }
    /* =====================PORTB On change external interrupt End=========================*/
    
    /* =====================ADC Module interrupt start=====================================*/
    if ((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF == INTERRUPT_OCCUR)){
        ADC_ISR();
    }
    else { /* Nothing */ }
    /* =====================ADC Module interrupt End=====================================*/
    /* =====================TIMER0 Module interrupt start=====================================*/
    if ((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF == INTERRUPT_OCCUR)){
        TMR0_ISR();
    }
    else { /* Nothing */ }
    /* =====================TIMER0 Module interrupt End=====================================*/
    /* =====================TIMER1 Module interrupt start=====================================*/
    if ((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF == INTERRUPT_OCCUR)){
        TMR1_ISR();
    }
    else { /* Nothing */ }
    /* =====================TIMER1 Module interrupt End=====================================*/
}

#endif