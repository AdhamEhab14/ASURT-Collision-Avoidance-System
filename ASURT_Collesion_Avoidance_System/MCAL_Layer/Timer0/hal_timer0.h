/* 
 * File:   hal_timer0.h
 * Author: omar fathy
 *
 * Created on 10 July 2024, 23:54
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* INCLUDES */
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* MACRO DECLARATIONS */
#define TIMER0_PRESCALER_ENABLE_CFG  1
#define TIMER0_PRESCALER_DISABLE_CFG 0

#define TIMER0_RISING_EDGE_CFG       1
#define TIMER0_FALLING_EDGE_CFG      0

#define TIMER0_TIMER_MODE            1
#define TIMER0_COUNTER_MODE          0

#define TIMER0_8BIT_REGISTER_MODE    1
#define TIMER0_16BIT_REGISTER_MODE   0

/* MACRO FUNCTIONS DECLARATIONS */
#define TIMER0_PRESCALER_ENABLE()    (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()   (T0CONbits.PSA = 1)

#define TIMER0_RISING_EDGE()         (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE()        (T0CONbits.T0SE = 1)

#define TIMER0_TIMER_MODE_ENABLE()   (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE() (T0CONbits.T0CS = 1)

#define TIMER0_8BIT_REGISTER_MODE_ENABLE()   (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE()  (T0CONbits.T08BIT = 0)

#define TIMER0_MODULE_ENABLE()          (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()         (T0CONbits.TMR0ON = 0)

/* DATA TYPES DECLARATIONS */
typedef enum{
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256
}timer0_prescaler_select_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR0_InterruptHandler)(void);
//    interrupt_priority_t priority;
#endif
    timer0_prescaler_select_t prescaler_value;
    uint16 preload_value;
    uint8 prescaler_enable : 1;
    uint8 counter_edge : 1;
    uint8 operation_mode : 1;
    uint8 register_size : 1;
    uint8 timer0_reserved : 4;
}timer0_t;

/* FUNCTIONS DECLARATIONS */
Std_ReturnType timer0_initialize(const timer0_t *timer);
Std_ReturnType timer0_deinitialize(const timer0_t *timer);
Std_ReturnType timer0_write_value(const timer0_t *timer, uint16 value);
Std_ReturnType timer0_read_value(const timer0_t *timer, uint16 *value);

#endif	/* HAL_TIMER0_H */

