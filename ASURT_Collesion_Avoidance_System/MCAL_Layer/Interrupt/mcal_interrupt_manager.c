/* 
 * File:   mcal_interrupt_manager.c
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_flag = 1 , RB5_flag = 1 , RB6_flag = 1 , RB7_flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptManagerHigh(void){
    
}

void __interrupt(low_priority) InterruptManagerLow(void){
    
}

#else

void __interrupt() InterruptManagerHigh(void){
    /* -------------------------------- INTx External Interrupt Start --------------------------------*/
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    /* --------------------------------- INTx External Interrupt End ---------------------------------*/
    
    /* ------------------------- PORTB External On Change Interrupt Start ----------------------------*/
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
            && (PORTBbits.RB4 == GPIO_HIGH) && (RB4_flag == 1)){
        RB4_flag = 0;
        RB4_ISR(0);
    }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
            && (PORTBbits.RB4 == GPIO_LOW) && (RB4_flag == 0)){
        RB4_flag = 1;
        RB4_ISR(1);
    }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
            && (PORTBbits.RB5 == GPIO_HIGH) && (RB5_flag == 1)){
        RB5_flag = 0; 
        RB5_ISR(0);
    }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
            && (PORTBbits.RB5 == GPIO_LOW)&& (RB5_flag == 0)){
        RB5_flag = 1; 
        RB5_ISR(1);
    }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
            && (PORTBbits.RB6 == GPIO_HIGH) && (RB6_flag == 1)){
        RB6_flag = 0;
        RB6_ISR(0);
    }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
            && (PORTBbits.RB6 == GPIO_LOW) && (RB6_flag == 0)){
        RB6_flag = 1;
        RB6_ISR(1);
    }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
            && (PORTBbits.RB7 == GPIO_HIGH) && (RB7_flag == 1)){
        RB7_flag = 0;
        RB7_ISR(0);
    }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) 
            && (PORTBbits.RB7 == GPIO_LOW) && (RB7_flag == 0)){
        RB7_flag = 1;
        RB7_ISR(1);
    }
    /* ----------------------- PORTB External On Change Interrupt End --------------------------*/
    
    /* -------------------------- ADC Module Interrupt Start -----------------------------------*/
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
    /* --------------------------- ADC Module Interrupt End -------------------------------------*/
    
    
    /* -------------------------- EUSART Module Interrupt Start -----------------------------------*/
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF)){
        EUSART_Tx_ISR();
    }
    
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF)){
        EUSART_Rx_ISR();
    }
    /* --------------------------- EUSART Module Interrupt End -------------------------------------*/

    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        TMR0_ISR();
    }
    
}

#endif