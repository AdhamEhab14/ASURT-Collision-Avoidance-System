/* 
 * File:   hal_eusart.c
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#include "hal_eusart.h"

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* EUSART_TxInterruptHandler)(void) = NULL;
#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* EUSART_RxInterruptHandler)(void) = NULL;
static void(* EUSART_FramingErrorHandler)(void) = NULL;
static void(* EUSART_OverrunErrorHandler)(void) = NULL;
#endif


static Std_ReturnType EUSART_Baud_Rate_Calculation(const eusart_t *_eusart_obj);
static Std_ReturnType EUSART_ASYNC_TX_Init(const eusart_t *_eusart_obj);
static Std_ReturnType EUSART_ASYNC_RX_Init(const eusart_t *_eusart_obj);

/**
 * @brief Initialize EUSART module
 * @param _eusart_obj pointer to the EUSART module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Init(const eusart_t *_eusart_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == _eusart_obj){
        retVal = E_NOT_OK;
    }
    else{
        /* Disable the EUSART module */
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        /* Configure RC6 and RC7 pins to be output */
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;
        /* Configure the baud-rate */
        retVal = EUSART_Baud_Rate_Calculation(_eusart_obj);
        /* Configure TX */
        retVal = EUSART_ASYNC_TX_Init(_eusart_obj);
        /* Configure RX*/
        retVal = EUSART_ASYNC_RX_Init(_eusart_obj);
        /* Enable the EUSART module */
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE;
        retVal = E_OK;
    }
    return retVal;
}

/**
 * @brief DeInitialize EUSART module
 * @param _eusart_obj pointer to the EUSART module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_DeInit(const eusart_t *_eusart_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == _eusart_obj){
        retVal = E_NOT_OK;
    }
    else{
        /* Disable EUSART */
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        /* Configure the interrupt */

        retVal = E_OK;
    }
    return retVal;
}




/**
 * @brief Reading a byte by blocking the CPU till the byte is read
 * @param _eusart_obj pointer to the EUSART module configurations
 * @param _data
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Read_Byte_Blocking(const eusart_t *_eusart_obj , uint8 *_data){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == _eusart_obj) || (NULL == _data)){
        retVal = E_NOT_OK;
    }
    else{
        while(!PIR1bits.RCIF);
        *_data = RCREG;
        retVal = E_OK;
    }
    return retVal;
}
/**
 * @brief Reading a byte without blocking the CPU till the byte is read
 * @param _eusart_obj pointer to the EUSART module configurations
 * @param _data
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Read_Byte_Non_Blocking(const eusart_t *_eusart_obj , uint8 *_data){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == _eusart_obj) || (NULL == _data)){
        retVal = E_NOT_OK;
    }
    else{
        if(1 == PIR1bits.RCIF){
            *_data = RCREG;
            retVal = E_OK;
        }
        else{
            retVal = E_NOT_OK;
        }
    }
    return retVal;
}

/**
 * @brief Restarting Rx by enabling and disabling CREN bit
 * @param _eusart_obj pointer to the EUSART module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_RX_Restart(const eusart_t *_eusart_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == _eusart_obj){
        retVal = E_NOT_OK;
    }
    else{
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    return retVal;
}



/**
 * @brief Writing a byte by blocking the CPU till the byte is written
 * @param _eusart_obj pointer to the EUSART module configurations
 * @param _data
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Write_Byte_Blocking(const eusart_t *_eusart_obj , uint8 _data){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == _eusart_obj){
        retVal = E_NOT_OK;
    }
    else{
        while(!TXSTAbits.TRMT);
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        EUSART_TX_InterruptEnable();
#endif
        TXREG = _data;
        retVal = E_OK;
    }
    return retVal;
}

Std_ReturnType EUSART_ASYNC_Write_String_Blocking(const eusart_t *_eusart_obj , uint8 *_data , uint32 _str_length){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == _eusart_obj){
        retVal = E_NOT_OK;
    }
    else{
        for(uint16 counter = 0; counter < _str_length ; counter++){
            retVal = EUSART_ASYNC_Write_Byte_Blocking(_eusart_obj , _data[counter]);
        }
    }
    return retVal;
}

/**
 * @brief Writing a byte without blocking the CPU till the byte is written
 * @param _eusart_obj pointer to the EUSART module configurations
 * @param _data
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Write_Byte_Non_Blocking(const eusart_t *_eusart_obj , uint8 _data){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == _eusart_obj){
        retVal = E_NOT_OK;
    }
    else{
        if(1 == PIR1bits.TXIF){
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        EUSART_TX_InterruptEnable();
#endif
        TXREG = _data;
        retVal = E_OK;
        }
        else{
            retVal = E_NOT_OK;
        }
    }
    return retVal;
}
/**
 * @brief Writing a string without blocking the CPU till the byte is written
 * @param _eusart_obj pointer to the EUSART module configurations
 * @param _data
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Write_String_Non_Blocking(const eusart_t *_eusart_obj , uint8 *_data , uint32 _str_length){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == _eusart_obj) || (NULL == _data)){
        retVal = E_NOT_OK;
    }
    else{
        for(uint16 counter = 0; counter < _str_length ; counter++){
            retVal = EUSART_ASYNC_Write_Byte_Non_Blocking(_eusart_obj , _data[counter]);
        }
    }
    return retVal;
}

/*--------------------------------- Helper Functions --------------------------------------*/

static Std_ReturnType EUSART_Baud_Rate_Calculation(const eusart_t *_eusart_obj){
    Std_ReturnType retVal = E_NOT_OK;
    float baud_rate_temp = 0;
    if(NULL == _eusart_obj){
        retVal = E_NOT_OK;
    }
    else{
        switch(_eusart_obj->baudrate_config){
            case BAUDRATE_ASYN_8BIT_lOW_SPEED : 
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
                baud_rate_temp = ((_XTAL_FREQ / (float)(_eusart_obj->baudrate)) / 64) - 1;
                break;
            case BAUDRATE_ASYN_8BIT_HIGH_SPEED : 
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
                baud_rate_temp = ((_XTAL_FREQ / (float)(_eusart_obj->baudrate)) / 16) - 1;
                break;
            case BAUDRATE_ASYN_16BIT_lOW_SPEED : 
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                baud_rate_temp = ((_XTAL_FREQ / (float)(_eusart_obj->baudrate)) / 16) - 1;
                break;
            case BAUDRATE_ASYN_16BIT_HIGH_SPEED : 
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                baud_rate_temp = ((_XTAL_FREQ / (float)(_eusart_obj->baudrate)) / 4) - 1;
                break;
            case BAUDRATE_SYN_8BIT : 
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
                baud_rate_temp = ((_XTAL_FREQ / (float)(_eusart_obj->baudrate)) / 4) - 1;
                break;
            case BAUDRATE_SYN_16BIT : 
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                baud_rate_temp = ((_XTAL_FREQ / (float)(_eusart_obj->baudrate)) / 4) - 1;
                break;
            default:
                retVal = E_NOT_OK;
        }
        SPBRG = (uint8)((uint32)baud_rate_temp);
        SPBRGH = (uint8)(((uint32)baud_rate_temp) >> 8);
        retVal = E_OK;
    }
    return retVal;
}



static Std_ReturnType EUSART_ASYNC_TX_Init(const eusart_t *_eusart_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == _eusart_obj){
        retVal = E_NOT_OK;
    }
    else{
        if(EUSART_ASYNCHRONOUS_TX_ENABLE == _eusart_obj->eusart_tx_cfg.eusart_tx_enable){ 
            /* Enable TX */
            TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
            
            /* EUSART Transmit Interrupt Configurations */
            if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE == _eusart_obj->eusart_tx_cfg.eusart_tx_interrupt_enable){
                PIE1bits.TX1IE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE;
                /* Configure the interrupts */
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        EUSART_TX_InterruptEnable();    /* Enable EUSART_TX module interrupt */
        EUSART_TxInterruptHandler = _eusart_obj->EUSART_TxInterruptHandler;
        /* Check priority & Enable EUSART_TX module interrupt */
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY == _eusart_obj->eusart_tx_cfg.eusart_tx_interrupt_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            EUSART_TX_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _eusart_obj->eusart_tx_cfg.eusart_tx_interrupt_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            EUSART_TX_LowPrioritySet();
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
#endif
            }
            else if(EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE == _eusart_obj->eusart_tx_cfg.eusart_tx_interrupt_enable){
                PIE1bits.TX1IE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
            }
            
            /* EUSART Transmit 9-Bit Configurations */
            if(EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == _eusart_obj->eusart_tx_cfg.eusart_tx_9bit_enable){
                TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
            }
            else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE == _eusart_obj->eusart_tx_cfg.eusart_tx_9bit_enable){
                TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
            }
        
        }
        else {/* Nothing */}
        retVal = E_OK;
    }
    return retVal;
}


static Std_ReturnType EUSART_ASYNC_RX_Init(const eusart_t *_eusart_obj){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == _eusart_obj){
        retVal = E_NOT_OK;
    }
    else{
        if(EUSART_ASYNCHRONOUS_RX_ENABLE == _eusart_obj->eusart_rx_cfg.eusart_rx_enable){ 
            /* Enable RX */
            RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
            
            /* EUSART Receiver Interrupt Configurations */
            if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE == _eusart_obj->eusart_rx_cfg.eusart_rx_interrupt_enable){
                PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
                /* Configure the interrupts */
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        EUSART_RX_InterruptEnable();    /* Enable EUSART_RX module interrupt */
        EUSART_RxInterruptHandler = _eusart_obj->EUSART_RxInterruptHandler;
        EUSART_FramingErrorHandler = _eusart_obj->EUSART_FramingErrorHandler;
        EUSART_OverrunErrorHandler = _eusart_obj->EUSART_OverrunErrorHandler;
        /* Check priority & Enable EUSART_RX module interrupt */
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY == _eusart_obj->eusart_rx_cfg.eusart_rx_interrupt_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            EUSART_RX_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _eusart_obj->eusart_rx_cfg.eusart_rx_interrupt_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            EUSART_RX_LowPrioritySet();
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
#endif
            }
            else if(EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE == _eusart_obj->eusart_rx_cfg.eusart_rx_interrupt_enable){
                PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
            }
            /* EUSART Receiver 9-Bit Configurations */
            if(EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE == _eusart_obj->eusart_rx_cfg.eusart_rx_9bit_enable){
                RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE;
            }
            else if(EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE == _eusart_obj->eusart_rx_cfg.eusart_rx_9bit_enable){
                RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
            }
        
        }
        else {/* Nothing */}
        retVal = E_OK;
    }
    return retVal;
}

/*--------------------------------------- ISRs -------------------------------------------*/

void EUSART_Tx_ISR(void){
    EUSART_TX_InterruptDisable();
    if(EUSART_TxInterruptHandler){
        EUSART_TxInterruptHandler();
    }
}
void EUSART_Rx_ISR(void){
    if(EUSART_RxInterruptHandler){
        EUSART_RxInterruptHandler();
    }
    if(EUSART_FramingErrorHandler){
        EUSART_FramingErrorHandler();
    }
    if(EUSART_OverrunErrorHandler){
        EUSART_OverrunErrorHandler();
    }
}