/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/***************************************Includes***************************************/

/***********************************Macro Declarations**********************************/

#define INTERRUPT_FEATURE_ENABLE 1U

//#define INTERRUPT_PRIORITY_LEVELS_ENABLE                INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INTERRUPT_INTx_FEATRUE_ENABLE          INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_ON_CHANGE_FEATRUE_ENABLE     INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_FEATURE_ENABLE                    INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_FEATURE_ENABLE                 INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEATURE_ENABLE                 INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEATURE_ENABLE                 INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEATURE_ENABLE                 INTERRUPT_FEATURE_ENABLE

#define CCP1_INTERRUPT_FEATURE_ENABLE                   INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE_ENABLE                   INTERRUPT_FEATURE_ENABLE

#define EUSART_TX_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE
#define EUSART_RX_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE

#define MSSP_SPI_INTERRUPT_FEATURE_ENABLE               INTERRUPT_FEATURE_ENABLE
#define MSSP_I2C_INTERRUPT_FEATURE_ENABLE               INTERRUPT_FEATURE_ENABLE

/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

/***********************************Function Declarations*******************************/

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

