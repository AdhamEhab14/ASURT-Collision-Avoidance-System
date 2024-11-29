/* 
 * File:   mcal_internal_interrupt.h
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/***************************************Includes***************************************/

#include "mcal_interrupt_config.h"

/***********************************Macro Declarations**********************************/

/******************************Macro Function Declarations******************************/

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the ADC module */
#define ADC_InterruptDisable() (PIE1bits.ADIE = 0)
/* This routine sets the interrupt enable for the ADC module */
#define ADC_InterruptEnable() (PIE1bits.ADIE = 1)
/* This routine clears the interrupt flag for the ADC module */
#define ADC_InterruptFlagClear() (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine sets high priority of the ADC module */
#define ADC_HighPrioritySet() (IPR1bits.ADIP = 1)
/* This routine sets low priority of the ADC module */
#define ADC_LowPrioritySet() (IPR1bits.ADIP = 0)
#endif
#endif

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the Timer0 module */
#define TIMER0_InterruptDisable() (INTCONbits.TMR0IE = 0)
/* This routine sets the interrupt enable for the Timer0 module */
#define TIMER0_InterruptEnable() (INTCONbits.TMR0IE = 1)
/* This routine clears the interrupt flag for the Timer2 module */
#define TIMER0_InterruptFlagClear() (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine sets high priority of the Timer0 module */
#define TIMER0_HighPrioritySet() (IPR1bits.TMR0IP = 1)
/* This routine sets low priority of the Timer0 module */
#define TIMER0_LowPrioritySet() (IPR1bits.TMR0IP = 0)
#endif
#endif



#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the EUSART_TX module */
#define EUSART_TX_InterruptDisable() (PIE1bits.TXIE = 0)
/* This routine sets the interrupt enable for the EUSART_TX module */
#define EUSART_TX_InterruptEnable() (PIE1bits.TXIE = 1)
/* This routine clears the interrupt flag for the EUSART_TX module */
#define EUSART_TX_InterruptFlagClear() (PIR1bits.TXIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine sets high priority of the EUSART_TX module */
#define EUSART_TX_HighPrioritySet() (IPR1bits.TXIP = 1)
/* This routine sets low priority of the EUSART_TX module */
#define EUSART_TX_LowPrioritySet() (IPR1bits.TXIP = 0)
#endif
#endif


#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the EUSART_RX module */
#define EUSART_RX_InterruptDisable() (PIE1bits.RCIE = 0)
/* This routine sets the interrupt enable for the EUSART_RX module */
#define EUSART_RX_InterruptEnable() (PIE1bits.RCIE = 1)
/* This routine clears the interrupt flag for the EUSART_RX module */
#define EUSART_RX_InterruptFlagClear() (PIR1bits.RCIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine sets high priority of the EUSART_RX module */
#define EUSART_RX_HighPrioritySet() (IPR1bits.RCIP = 1)
/* This routine sets low priority of the EUSART_RX module */
#define EUSART_RX_LowPrioritySet() (IPR1bits.RCIP = 0)
#endif
#endif


/***********************************Datatype Declarations*******************************/

/***********************************Function Declarations*******************************/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

