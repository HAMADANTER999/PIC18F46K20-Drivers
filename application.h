/* 
 * File:   application.h
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 11:02 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : includes*/

#include <stdio.h>
#include <stdlib.h>
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/Button/ecu_button.h"
#include "ECU_Layer/Relay/ecu_relay.h"
#include "ECU_Layer/DC_Motor/ecu_dc_motor.h"

/* Section : Macro Declarations*/
#define _XTAL_FREQ      8000000UL
/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/

/* Section : Function Declarations*/
void Application (void);

#endif	/* APPLICATION_H */

