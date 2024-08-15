/* 
 * File:   ecu_seven_seg.h
 * Author: anter
 *
 * Created on August 15, 2024, 7:07 PM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/* Section : includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_seven_seg_cfg.h"


/* Section : Macro Declarations*/

/* Section : Macro Function Declarations*/

/* Section : Data type Declarations*/

typedef enum {
    SEGMENT_COMMON_ANODE = 0,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct {
    pin_config_t segments_pins[4];
    segment_type_t segment_type;
}segment_t;
/* Section : Function Declarations*/
Std_ReturnType seven_segment_intialize(const segment_t *seg);
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number);


#endif	/* ECU_SEVEN_SEG_H */

