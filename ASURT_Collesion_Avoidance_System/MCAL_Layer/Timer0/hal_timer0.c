/* 
 * File:   hal_timer0.h
 * Author: omar fathy
 *
 * Created on 10 July 2024, 23:54
 */

#include "hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (* TMR0_InterruptHandler)(void) = NULL;
#endif

static uint16 Timer0_preload = 0;

static inline void timer0_prescaler_cfg(const timer0_t *timer);
static inline void timer0_mode_select(const timer0_t *timer);
static inline void timer0_register_size_cfg(const timer0_t *timer);

/**
 * @brief Initialize the Timer0 module
 * @param timer (Pointer to the timer configuration)
 * @return State of the function
 */
Std_ReturnType timer0_initialize(const timer0_t *timer){
    Std_ReturnType ret = E_NOT_OK;
    
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
        timer0_prescaler_cfg(timer);
        timer0_mode_select(timer);
        timer0_register_size_cfg(timer);
        TMR0H = (uint8)((timer->preload_value) >> 8);
        TMR0L = (uint8)(timer->preload_value);
        Timer0_preload = timer->preload_value;
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        TMR0_InterruptHandler = timer->TMR0_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(timer->priority == INTERRUPT_PRIORITY_HIGH){
            INTERRUPT_GlobalInterruptEnableHigh();
            Timer0_SetHighPriority();
        }
        else if(timer->priority == INTERRUPT_PRIORITY_LOW){
            INTERRUPT_GlobalInterruptEnableLow();
            Timer0_SetlowPriority();
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TIMER0_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Deinitialize the Timer0 module
 * @param timer (Pointer to the timer configuration)
 * @return State of the function
 */
Std_ReturnType timer0_deinitialize(const timer0_t *timer){
    Std_ReturnType ret = E_NOT_OK;
    
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        Timer0_Interrupt_Disable();
#endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Write value in the timer0 register
 * @param timer (Pointer to the timer configuration)
 * @param value (The value to write in the timer register)
 * @return State of the function
 */
Std_ReturnType timer0_write_value(const timer0_t *timer, uint16 value){
    Std_ReturnType ret = E_NOT_OK;
    
    if(timer == NULL){
        ret = E_NOT_OK;
    }
    else{
        TMR0H = (uint8)((timer->preload_value) >> 8);
        TMR0L = (uint8)(timer->preload_value);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Write value in the timer0 register
 * @param timer (Pointer to the timer configuration)
 * @param value (Pointer to the value read from the timer register)
 * @return State of the function
 */
Std_ReturnType timer0_read_value(const timer0_t *timer, uint16 *value){
    Std_ReturnType ret = E_NOT_OK;
    
    if((timer == NULL) || (value == NULL)){
        ret = E_NOT_OK;
    }
    else{
        uint8 l_tmr0h = 0, l_tmr0l = 0;
        l_tmr0h = TMR0H;
        l_tmr0l = TMR0L;
        *value = (uint16)((l_tmr0h << 8) + l_tmr0l);
        ret = E_OK;
    }
    return ret;
}

void TMR0_ISR(void){
    TIMER0_InterruptFlagClear();
    TMR0H = (uint8)(Timer0_preload >> 8);
    TMR0L = (uint8)Timer0_preload;
    if(TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
}

static inline void timer0_prescaler_cfg(const timer0_t *timer){
    if(timer->prescaler_enable == TIMER0_PRESCALER_ENABLE_CFG){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = timer->prescaler_value;
    }
    else if(timer->prescaler_enable == TIMER0_PRESCALER_DISABLE_CFG){
        TIMER0_PRESCALER_DISABLE();
    }
}

static inline void timer0_mode_select(const timer0_t *timer){
    if(timer->operation_mode == TIMER0_TIMER_MODE){
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if(timer->operation_mode == TIMER0_COUNTER_MODE){
        TIMER0_COUNTER_MODE_ENABLE();
        if(timer->counter_edge == TIMER0_RISING_EDGE_CFG){
            TIMER0_RISING_EDGE();
        }
        else if(timer->counter_edge == TIMER0_FALLING_EDGE_CFG){
            TIMER0_FALLING_EDGE();
        }
    }
}

static inline void timer0_register_size_cfg(const timer0_t *timer){
    if(timer->register_size == TIMER0_8BIT_REGISTER_MODE){
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
    else if(timer->register_size == TIMER0_16BIT_REGISTER_MODE){
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    }
}