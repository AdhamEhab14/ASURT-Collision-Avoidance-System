/* 
 * File:   mcal_external_interrupt.h
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/***************************************Includes***************************************/

#include "mcal_interrupt_config.h"

/***********************************Macro Declarations**********************************/

#if EXTERNAL_INTERRUPT_INTx_FEATRUE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine sets the interrupt enable for the external interrupt , INT0 */
#define EXT_INT0_InterruptEnable() (INTCONbits.INT0IE = 1)
/* This routine clears the interrupt enable for the external interrupt , INT0 */
#define EXT_INT0_InterruptDisable() (INTCONbits.INT0IE = 0)
/* This routine clears the interrupt flag for the external interrupt , INT0*/
#define EXT_INT0_InterruptFlagClear() (INTCONbits.INT0IF = 0)
/* This routine sets the edge detect of the external interrupt to negative edge , INT0*/
#define EXT_INT0_RisingEdge() (INTCON2bits.INTEDG0 = 1)
/* This routine sets the edge detect of the external interrupt to positive edge , INT0*/
#define EXT_INT0_FalingEdge() (INTCON2bits.INTEDG0 = 0)


/* This routine sets the interrupt enable for the external interrupt , INT1 */
#define EXT_INT1_InterruptEnable() (INTCON3bits.INT1IE = 1)
/* This routine clears the interrupt enable for the external interrupt , INT1 */
#define EXT_INT1_InterruptDisable() (INTCON3bits.INT1IE = 0)
/* This routine clears the interrupt flag for the external interrupt , INT1*/
#define EXT_INT1_InterruptFlagClear() (INTCON3bits.INT1IF = 0)
/* This routine sets the edge detect of the external interrupt to negative edge , INT1*/
#define EXT_INT1_RisingEdge() (INTCON2bits.INTEDG1 = 1)
/* This routine sets the edge detect of the external interrupt to positive edge , INT1*/
#define EXT_INT1_FalingEdge() (INTCON2bits.INTEDG1 = 0)

/* This routine sets the interrupt enable for the external interrupt , INT2 */
#define EXT_INT2_InterruptEnable() (INTCON3bits.INT2IE = 1)
/* This routine clears the interrupt enable for the external interrupt , INT2 */
#define EXT_INT2_InterruptDisable() (INTCON3bits.INT2IE = 0)
/* This routine clears the interrupt flag for the external interrupt , INT2*/
#define EXT_INT2_InterruptFlagClear() (INTCON3bits.INT2IF = 0)
/* This routine sets the edge detect of the external interrupt to negative edge , INT2*/
#define EXT_INT2_RisingEdge() (INTCON2bits.INTEDG2 = 1)
/* This routine sets the edge detect of the external interrupt to positive edge , INT2*/
#define EXT_INT2_FalingEdge() (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine sets high priority of the external interrupt , INT1 */
#define EXT_INT1_HighPrioritySet() (INTCON3bits.INT1IP = 1)
/* This routine sets low priority of the external interrupt , INT1 */
#define EXT_INT1_LowPrioritySet() (INTCON3bits.INT1IP = 0)
/* This routine sets high priority of the external interrupt , INT2 */
#define EXT_INT2_HighPrioritySet() (INTCON3bits.INT2IP = 1)
/* This routine sets low priority of the external interrupt , INT2 */
#define EXT_INT2_LowPrioritySet() (INTCON3bits.INT2IP = 0)
#endif

#endif

#if EXTERNAL_INTERRUPT_ON_CHANGE_FEATRUE_ENABLE==INTERRUPT_FEATURE_ENABLE

/* This routine sets the interrupt enable the external interrupt , RBx */
#define EXT_RBx_InterruptEnable() (INTCONbits.RBIE = 1)
/* This routine clears the interrupt enable the external interrupt , RBx */
#define EXT_RBx_InterruptDisable() (INTCONbits.RBIE = 0)
/* This routine clears the interrupt flag for the external interrupt , RBx*/
#define EXT_RBx_InterruptFlagClear() (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine sets high priority of the external interrupt , RBx */
#define EXT_RBx_HighPrioritySet() (INTCON2bits.RBIP = 1)
/* This routine sets low priority of the external interrupt , RBx */
#define EXT_RBx_LowPrioritySet() (INTCON2bits.RBIP = 0)
#endif

#endif


/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

/* INTx external interrupts rising and falling edge */
typedef enum{
    INTERRUPT_FALLING_EDGE,
    INTERRUPT_RISING_EDGE        
}interrupt_INTx_edge;
/* INTx external interrupts sources */
typedef enum{
    INTERRUPT_EXTERNAL_INT0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2        
}interrupt_INTx_src;
/* INTx external interrupts configurations */
typedef struct{
    void(* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src source;
    interrupt_priority_cfg priority;
}interrupt_INTx_t;
/* RBx external interrupts configurations */
typedef struct{
    void(* EXT_InterruptHandler_HIGH)(void);
    void(* EXT_InterruptHandler_LOW)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_t;

/***********************************Function Declarations*******************************/

/**
 * @brief Initializing an external interrupt , INTx
 * @param int_obj pointer to the INTX external interrupts configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj);
/**
 * @brief Deinitializing an external interrupt , INTx
 * @param int_obj pointer to the INTX external interrupts configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);

/**
 * @brief Initializing an external interrupt , RBx
 * @param int_obj pointer to the RBX external interrupts configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj);
/**
 * @brief Deinitializing an external interrupt , RBx
 * @param int_obj pointer to the RBX external interrupts configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

