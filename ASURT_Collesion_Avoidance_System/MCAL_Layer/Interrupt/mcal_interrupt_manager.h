/* 
 * File:   mcal_interrupt_manager.h
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */
#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/***************************************Includes***************************************/

#include "mcal_interrupt_config.h"

/***********************************Macro Declarations**********************************/

/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_Source);
void RB5_ISR(uint8 RB5_Source);
void RB6_ISR(uint8 RB6_Source);
void RB7_ISR(uint8 RB7_Source);
void ADC_ISR(void);
void TMR0_ISR(void);
void EUSART_Tx_ISR(void);
void EUSART_Rx_ISR(void);

/***********************************Function Declarations*******************************/

#endif	/* MCAL_INTERRUPT_MANAGER_H */

