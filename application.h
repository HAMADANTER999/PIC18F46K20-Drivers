/* 
 * File:   application.h
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 11:02 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : includes*/

#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "ECU_Layer/chr_lcd/ecu_chr_lcd.h"
#include "MCAL_Layer/Timer0/hal_timer0.h"
#include "MCAL_Layer/Timer1/hal_timer1.h"
#include "MCAL_Layer/Timer2/hal_timer2.h"
#include "MCAL_Layer/Timer3/hal_timer3.h"
#include "MCAL_Layer/CCP1/hal_ccp1.h"

/* Section : Macro Declarations*/
#define _XTAL_FREQ      8000000UL
/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/

/* Section : Function Declarations*/
void Application (void);

#endif	/* APPLICATION_H */

