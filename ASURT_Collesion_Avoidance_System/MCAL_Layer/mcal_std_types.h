/* 
 * File:   mcal_std_types.h
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/***************************************Includes***************************************/

#include "std_libraries.h"
#include "compiler.h"

/***********************************Macro Declarations**********************************/

#define STD_HIGH        0x01;
#define STD_LOW         0x00;

#define STD_ON          0x01;
#define STD_OFF         0x00;

#define STD_ACTIVE      0x01;
#define STD_IDLE        0x00;

#define E_OK            (Std_ReturnType)0x01
#define E_NOT_OK        (Std_ReturnType)0x00

/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

typedef uint8 Std_ReturnType;

/***********************************Function Declarations*******************************/

#endif	/* MCAL_STD_TYPES_H */

