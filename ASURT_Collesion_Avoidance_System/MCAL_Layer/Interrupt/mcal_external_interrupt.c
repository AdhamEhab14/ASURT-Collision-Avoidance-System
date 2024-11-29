/* 
 * File:   mcal_external_interrupt.c
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#include "mcal_external_interrupt.h"

static void (*INT0_InterruptHandler)(void) = NULL;
static void (*INT1_InterruptHandler)(void) = NULL;
static void (*INT2_InterruptHandler)(void) = NULL;

static void (*RB4_InterruptHandler_HIGH)(void) = NULL;
static void (*RB4_InterruptHandler_LOW)(void) = NULL;
static void (*RB5_InterruptHandler_HIGH)(void) = NULL;
static void (*RB5_InterruptHandler_LOW)(void) = NULL;
static void (*RB6_InterruptHandler_HIGH)(void) = NULL;
static void (*RB6_InterruptHandler_LOW)(void) = NULL;
static void (*RB7_InterruptHandler_HIGH)(void) = NULL;
static void (*RB7_InterruptHandler_LOW)(void) = NULL;

/*------------------------------------------------------------------------------------------------------*/

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler(void)));
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler(void)));
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler(void)));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);

/*------------------------------------------------------------------------------------------------------*/

void INT0_ISR(void){
    /* The INT0 external interrupt occurred (must be cleared in software) */
    EXT_INT0_InterruptFlagClear();
    /* Code : to be executed from MCAL interrupt context */
    
    /* Application callback function gets called every time this ISR executes*/
    if(INT0_InterruptHandler){
        INT0_InterruptHandler();
    }
}
void INT1_ISR(void){
    /* The INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT1_InterruptFlagClear();
    /* Code : to be executed from MCAL interrupt context */
    
    /* Application callback function gets called every time this ISR executes*/
    if(INT1_InterruptHandler){
        INT1_InterruptHandler();
    }
}
void INT2_ISR(void){
    /* The INT2 external interrupt occurred (must be cleared in software) */
    EXT_INT2_InterruptFlagClear();
    /* Code : to be executed from MCAL interrupt context */
    
    /* Application callback function gets called every time this ISR executes*/
    if(INT2_InterruptHandler){
        INT2_InterruptHandler();
    }
}

void RB4_ISR(uint8 RB4_Source){
    /* The RB4 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : to be executed from MCAL interrupt context */
    /* Application callback function gets called every time this ISR executes*/
    if(0 == RB4_Source){
        if(RB4_InterruptHandler_HIGH){
            RB4_InterruptHandler_HIGH();
        }
    }
    else if(1 == RB4_Source){
        if(RB4_InterruptHandler_LOW){
            RB4_InterruptHandler_LOW();
        }
    }
}
void RB5_ISR(uint8 RB5_Source){
    /* The RB5 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : to be executed from MCAL interrupt context */
    /* Application callback function gets called every time this ISR executes*/
    if(0 == RB5_Source){
        if(RB5_InterruptHandler_HIGH){
            RB5_InterruptHandler_HIGH();
        }
    }
    else if(1 == RB5_Source){
        if(RB5_InterruptHandler_LOW){
            RB5_InterruptHandler_LOW();
        }
    }
}
void RB6_ISR(uint8 RB6_Source){
    /* The RB6 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : to be executed from MCAL interrupt context */
    /* Application callback function gets called every time this ISR executes*/
    if(0 == RB6_Source){
        if(RB6_InterruptHandler_HIGH){
            RB6_InterruptHandler_HIGH();
        }
    }
    else if(1 == RB6_Source){
        if(RB6_InterruptHandler_LOW){
            RB6_InterruptHandler_LOW();
        }
    }
}
void RB7_ISR(uint8 RB7_Source){
    /* The RB7 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code : to be executed from MCAL interrupt context */
    /* Application callback function gets called every time this ISR executes*/
    if(0 == RB7_Source){
        if(RB7_InterruptHandler_HIGH){
            RB7_InterruptHandler_HIGH();
        }
    }
    else if(1 == RB7_Source){
        if(RB7_InterruptHandler_LOW){
            RB7_InterruptHandler_LOW();
        }
    }
}

/*------------------------------------------------------------------------------------------------------*/

/**
 * @brief Initializing an external interrupt , INTx
 * @param int_obj pointer to the INTX external interrupts configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        /* Disable the external interrupt */
        retVal = Interrupt_INTx_Disable(int_obj);
        /* Clear the interrupt flag : external interrupt did not occur */
        retVal &= Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure external interrupt edge */
        retVal &= Interrupt_INTx_Edge_Init(int_obj);
        /* Configure external interrupt priority */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        retVal = Interrupt_INTx_Priority_Init(int_obj);
#endif
        /* Configure external interrupt I/O pin */
        retVal &= Interrupt_INTx_Pin_Init(int_obj);  
        /* Configure default interrupt callback */
        retVal &= Interrupt_INTx_SetInterruptHandler(int_obj); 
        /* Enable the external interrupt */
        retVal &= Interrupt_INTx_Enable(int_obj);
    }
    return retVal;
}

/**
 * @brief Deinitializing an external interrupt , INTx
 * @param int_obj pointer to the INTX external interrupts configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        retVal = Interrupt_INTx_Disable(int_obj);
    }
    return retVal;
}


/**
 * @brief Initializing an external interrupt , RBx
 * @param int_obj pointer to the RBX external interrupts configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        /* Disable the external interrupt */
        retVal = Interrupt_RBx_Disable(int_obj);
        /* Clear the interrupt flag : external interrupt did not occur */
        EXT_RBx_InterruptFlagClear();
        /* Configure external interrupt priority */
        retVal = Interrupt_RBx_Priority_Init(int_obj);
        /* Configure external interrupt I/O pin */
        retVal = Interrupt_RBx_Pin_Init(int_obj);
        /* Configure default interrupt callback */
        switch(int_obj->mcu_pin.pin){
            case GPIO_PIN4 : 
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN5 : 
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN6 : 
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN7 : 
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            default : 
                retVal = E_NOT_OK;
        }
        /* Enable the external interrupt */
        retVal = Interrupt_RBx_Enable(int_obj);
    }
    return retVal;
}
/**
 * @brief Deinitializing an external interrupt , RBx
 * @param int_obj pointer to the RBX external interrupts configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        retVal = Interrupt_RBx_Disable(int_obj);
        EXT_RBx_InterruptFlagClear();
    }
    return retVal;
}

/*--------------------------------------Helper functions---------------------------------------*/

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable();
                retVal = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowEnable();   
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_InterruptEnable();
                retVal = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowEnable();   
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_InterruptEnable();
                retVal = E_OK;
                break;
            default : retVal = E_NOT_OK;
        }
    }
    return retVal;
}
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptDisable();
                retVal = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_InterruptDisable();
                retVal = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_InterruptDisable();
                retVal = E_OK;
                break;
            default : retVal = E_NOT_OK;
        }
    }
    return retVal;
}
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    EXT_INT1_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                   EXT_INT1_HighPrioritySet();
                }
                retVal = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    EXT_INT2_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                   EXT_INT2_HighPrioritySet();
                }
                retVal = E_OK;
                break;
            default : retVal = E_NOT_OK;
        }
    }
    return retVal;
}
#endif
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){
                    EXT_INT0_FalingEdge();
                }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){
                    EXT_INT0_RisingEdge();
                }
                retVal = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){
                    EXT_INT1_FalingEdge();
                }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){
                    EXT_INT1_RisingEdge();
                }
                retVal = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){
                    EXT_INT2_FalingEdge();
                }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){
                    EXT_INT2_RisingEdge();
                }
                retVal = E_OK;
                break;
            default : retVal = E_NOT_OK;
        }
    }
    return retVal;
}
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        retVal = gpio_pin_initialize(&(int_obj->mcu_pin));
    }
    return retVal;
}
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptFlagClear();
                retVal = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_InterruptFlagClear();
                retVal = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_InterruptFlagClear();
                retVal = E_OK;
                break;
            default : retVal = E_NOT_OK;
        }
    }
    return retVal;
}

/*------------------------------------------------------------------------------------------------------*/

static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler(void))){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == InterruptHandler){
        retVal = E_NOT_OK;
    }
    else{
        INT0_InterruptHandler = InterruptHandler;
        retVal = E_OK; 
    }
    return retVal;
}
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler(void))){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == InterruptHandler){
        retVal = E_NOT_OK;
    }
    else{
        INT1_InterruptHandler = InterruptHandler;
        retVal = E_OK; 
    }
    return retVal;
}
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler(void))){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == InterruptHandler){
        retVal = E_NOT_OK;
    }
    else{
        INT2_InterruptHandler = InterruptHandler;
        retVal = E_OK; 
    }
    return retVal;
}
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
        if(NULL == int_obj){
            retVal = E_NOT_OK;
        }
        else{
            switch(int_obj->source){
                case INTERRUPT_EXTERNAL_INT0 : 
                    retVal = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                    break;
                case INTERRUPT_EXTERNAL_INT1 : 
                    retVal = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                    break;
                case INTERRUPT_EXTERNAL_INT2 : 
                    retVal = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                    break;
                default : retVal = E_NOT_OK;
            }
        }
        return retVal;
}

/*------------------------------------------------------------------------------------------------------*/

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        EXT_RBx_InterruptEnable();
        retVal = E_OK;
    }
    return retVal;
}
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        EXT_RBx_InterruptDisable();
        retVal = E_OK;
    }
    return retVal;
}
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowEnable();   
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
        retVal = E_OK;
    }
    return retVal;
}
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == int_obj){
        retVal = E_NOT_OK;
    }
    else{
        retVal = gpio_pin_initialize(&(int_obj->mcu_pin));
        retVal = E_OK;
    }
    return retVal;
}