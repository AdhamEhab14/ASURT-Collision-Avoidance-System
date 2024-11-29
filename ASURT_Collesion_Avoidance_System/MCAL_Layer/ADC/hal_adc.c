/* 
 * File:   hal_adc.c
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */


#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(*ADC_InterruptHandler)(void) = NULL;  
#endif

static inline void adc_input_channel_port_config(adc_channel_select_t channel);


/**
 * @brief Initializing the ADC
 * @param adc pointer to the ADC configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Init(const adc_config_t *adc){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == adc){
        retVal = E_NOT_OK;
    }
    else{
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        
        /* Configure the acquisition time*/
        ADCON2bits.ACQT = adc->acquisition_time;
        
        /* Configure the conversion clock */
        ADCON2bits.ADCS = adc->conversion_clock;
        
        /* Configure the default channel */
        ADCON0bits.CHS = adc->adc_channel;
        adc_input_channel_port_config(adc->adc_channel);
        
        /* Configure the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_InterruptEnable();    /* Enable ADC module interrupt */
        ADC_InterruptFlagClear(); /* Clear flag */
        ADC_InterruptHandler = adc->ADC_InterruptHandler;
        /* Check priority & Enable ADC module interrupt */
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelEnable();
            if(INTERRUPT_HIGH_PRIORITY == adc->priotiry){
                INTERRUPT_GlobalInterruptHighEnable();
                ADC_HighPrioritySet();
            }
            else if(INTERRUPT_LOW_PRIORITY == adc->priotiry){
                INTERRUPT_GlobalInterruptLowEnable();
                ADC_LowPrioritySet();
            }
    #else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
    #endif
#endif
        
        /* Configure the result format */
        if(ADC_RIGHT_FORMAT == adc->result_format){
            ADC_RESULT_RIGHT_FORMAT();
        }
        else if(ADC_LEFT_FORMAT == adc->result_format){
            ADC_RESULT_LEFT_FORMAT();
        }
        else{
            ADC_RESULT_RIGHT_FORMAT();
        }
        
        /* Configure the voltage reference*/
        if(ADC_VOLTAGE_REF_ENABLE == adc->voltage_reference){
            ADC_ENABLE_VOLTAGE_REFERENCE();
        }
        else if(ADC_VOLTAGE_REF_DISABLE == adc->voltage_reference){
            ADC_DISABLE_VOLTAGE_REFERENCE();
        }
        else{
            ADC_DISABLE_VOLTAGE_REFERENCE();
        }
        
        /* Enable the ADC*/
        ADC_CONVERTER_ENABLE();
        
        retVal = E_OK;
    }
    return retVal;
}

/**
 * @brief DeInitializing the ADC
 * @param adc pointer to the ADC configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_DeInit(const adc_config_t *adc){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == adc){
        retVal = E_NOT_OK;
    }
    else{
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE();
        /* Configure the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_InterruptDisable();
#endif
        retVal = E_OK;
    }
    return retVal;
}

/**
 * @brief Select a desired channel for conversion
 * @param adc pointer to the ADC configurations
 * @param channel defines the channel available for conversion
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Select_Channel(const adc_config_t *adc , adc_channel_select_t channel){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == adc){
        retVal = E_NOT_OK;
    }
    else{
        ADCON0bits.CHS = channel;
        adc_input_channel_port_config(channel);
        retVal = E_OK;
    }
    return retVal;
}

/**
 * @brief Start conversion of a desired channel
 * @param adc pointer to the ADC configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Start_Conversion(const adc_config_t *adc){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == adc){
        retVal = E_NOT_OK;
    }
    else{
        ADC_START_CONVERSION();
        retVal = E_OK;
    }
    return retVal;
}

/**
 * @brief Check if the conversion is completed or n
 * @param adc pointer to the ADC configurations
 * @param conversion_status
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Is_Convertion_Done(const adc_config_t *adc , uint8 *conversion_status){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == adc) || (NULL == conversion_status)){
        retVal = E_NOT_OK;
    }
    else{
        *conversion_status = (uint8)!(ADCON0bits.GODONE);
        retVal = E_OK;
    }
    return retVal;
}

/**
 * @brief Get the Analog to Digital converted value
 * @param adc pointer to the ADC configurations
 * @param conversion_result
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Get_Conversion_Result(const adc_config_t *adc , uint16 *conversion_result){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == adc) || (NULL == conversion_result)){
        retVal = E_NOT_OK;
    }
    else{
        if(ADC_RIGHT_FORMAT == adc->result_format){
            *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_LEFT_FORMAT == adc->result_format){
            *conversion_result = (uint16)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else{
            *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        }
        retVal = E_OK;
    }
    return retVal;
}

/**
 * @brief Select the desired channel for conversion and get the analog to digital converted value
 * @param adc pointer to the ADC configurations
 * @param channel
 * @param conversion_result
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Get_Conversion_Blocking(const adc_config_t *adc , adc_channel_select_t channel , uint16 *conversion_result){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == adc) || (NULL == conversion_result)){
        retVal = E_NOT_OK;
    }
    else{
        retVal = ADC_Select_Channel(adc , channel);
        retVal = ADC_Start_Conversion(adc);
        while(ADCON0bits.GODONE);
        retVal = ADC_Get_Conversion_Result(adc , conversion_result);
    }
    return retVal;
}

Std_ReturnType ADC_Start_Conversion_Interrupt(const adc_config_t *adc , adc_channel_select_t channel){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == adc){
        retVal = E_NOT_OK;
    }
    else{
        retVal = ADC_Select_Channel(adc , channel);
        retVal = ADC_Start_Conversion(adc);
    }
    return retVal;
}


/*-------------------------------------- Helper Functions ------------------------------------------*/


static inline void adc_input_channel_port_config(adc_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA , _TRISA_RA0_POSN); break;
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA , _TRISA_RA1_POSN); break;
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA , _TRISA_RA2_POSN); break;
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA , _TRISA_RA3_POSN); break;
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA , _TRISA_RA5_POSN); break;
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE , _TRISE_RE0_POSN); break;
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE , _TRISE_RE1_POSN); break;
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE , _TRISE_RE2_POSN); break;
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB , _TRISB_RB2_POSN); break;
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB , _TRISB_RB3_POSN); break;
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB , _TRISB_RB1_POSN); break;
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB , _TRISB_RB4_POSN); break;
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB , _TRISB_RB0_POSN); break;
    }
}


void ADC_ISR(void){
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
}