/* 
 * File:   mcal_std_types.h
 * Author: Mohammed Antar
 *
 * Created on July 30, 2024, 6:41 PM
 */


#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : includes*/
#include "std_libraries.h"
#include "compiler.h"

/* Section : Macro Declarations*/

#define STD_HIGH       0x01
#define STD_LOW        0X00

#define STD_ON         0X01
#define STD_OFF        0X00

#define ACTIVE         0X01
#define IDLE           0X00

#define E_OK           (Std_ReturnType)0x01
#define E_NOT_OK       (Std_ReturnType)0x00

#define ZERO_INIT      0X00





/* Section : Macro Function Declarations*/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long   uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long   sint32;

typedef uint8 Std_ReturnType;



/* Section : Data type Declarations*/




/* Section : Function Declarations*/



#endif	/* MCAL_STD_TYPES_H */

