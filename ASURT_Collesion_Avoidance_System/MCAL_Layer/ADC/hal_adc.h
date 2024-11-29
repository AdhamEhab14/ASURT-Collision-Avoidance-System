/* 
 * File:   hal_adc.h
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */


#ifndef HAL_ADC_H
#define	HAL_ADC_H

/***************************************Includes***************************************/

#include "hal_adc_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include "pic18f4620.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/***********************************Macro Declarations**********************************/

/**
 *@brief All Pins before ANx is Configured as Analog Pin and the rest of them are Digital Pins
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F


#define ADC_RIGHT_FORMAT                0x01U
#define ADC_LEFT_FORMAT                 0x00U

#define ADC_VOLTAGE_REF_ENABLE          0x01U
#define ADC_VOLTAGE_REF_DISABLE         0x00U

#define ADC_CONVERSION_COMPLETED        0x01U
#define ADC_CONVERSION_IN_PROGRESS      0x00U

/******************************Macro Function Declarations******************************/

/* ADC Converstion Status : A/D in Progress / A/D Idle State */
#define ADC_CONVERSION_STATUS() (ADCON0bits.GODONE)
#define ADC_START_CONVERSION() (ADCON0bits.GODONE = 1)

/* ADC Enable/Disable */
#define ADC_CONVERTER_ENABLE() (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE() (ADCON0bits.ADON = 0)

/* Voltage Reference Enable : Use External Vref+ and Vref- on AN2 & AN3 
   Voltage Reference Disable : Use VSS & VDD */
#define ADC_ENABLE_VOLTAGE_REFERENCE() do{ADCON1bits.VCFG1 = 1;\
                                          ADCON1bits.VCFG0 = 1;\
                                         }while(0)
#define ADC_DISABLE_VOLTAGE_REFERENCE() do{ADCON1bits.VCFG1 = 0;\
                                          ADCON1bits.VCFG0 = 0;\
                                         }while(0)

/**
 * @breif Configure the pins to be Digital or Analog using macros like this : ADC_AN4_ANALOG_FUNCTIONALITY
 * @ref Analog-To-Digital Port Configuration Control
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG = _CONFIG)

/* ADC Result Format */
#define ADC_RESULT_RIGHT_FORMAT() (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT() (ADCON2bits.ADFM = 0)

/***********************************Datatype Declarations*******************************/

/**
 * @brief Analog Channel Select
 */
typedef enum{
    ADC_CHANNEL_AN0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,        
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12        
}adc_channel_select_t;

/**
 * @note Acquisition time (sampling time) is the time required for the ADC to capture the input voltage during sampling
 */
typedef enum{
    ADC_0_TAD,
    ADC_2_TAD,
    ADC_4_TAD,         
    ADC_6_TAD,         
    ADC_8_TAD,         
    ADC_12_TAD,         
    ADC_16_TAD,
    ADC_20_TAD,         
}adc_acquisition_time_t;

/**
 * @note If the ADC FRC clock source is selected, a delay of one TCY (Instruction Cycle)
 *       is added before the ADC clock starts, this allows the SLEEP instruction to be executed before starting a conversion.
 */
typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,       
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,        
    ADC_CONVERSION_CLOCK_FOSC_DIV_64               
}adc_conversion_clock_t;


typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler) (void);
    interrupt_priority_cfg priotiry;
#endif
    adc_acquisition_time_t acquisition_time;
    adc_conversion_clock_t conversion_clock;
    adc_channel_select_t adc_channel;
    uint8 voltage_reference : 1;
    uint8 result_format : 1;
    uint8 : 6;
}adc_config_t;

/***********************************Function Declarations*******************************/

/**
 * @brief Initializing the ADC
 * @param adc pointer to the ADC configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Init(const adc_config_t *adc);
/**
 * @brief DeInitializing the ADC
 * @param adc pointer to the ADC configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_DeInit(const adc_config_t *adc);
/**
 * @brief Select a desired channel for conversion
 * @param adc pointer to the ADC configurations
 * @param channel defines the channel available for conversion
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Select_Channel(const adc_config_t *adc , adc_channel_select_t channel);
/**
 * @brief Start conversion of a desired channel
 * @param adc pointer to the ADC configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Start_Conversion(const adc_config_t *adc);
/**
 * @brief Check if the conversion is completed or n
 * @param adc pointer to the ADC configurations
 * @param conversion_status
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Is_Convertion_Done(const adc_config_t *adc , uint8 *conversion_status);
/**
 * @brief Get the Analog to Digital converted value
 * @param adc pointer to the ADC configurations
 * @param conversion_result
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Get_Conversion_Result(const adc_config_t *adc , uint16 *conversion_result);
/**
 * @brief Select the desired channel for conversion and get the analog to digital converted value
 * @param adc pointer to the ADC configurations
 * @param channel
 * @param conversion_result
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Get_Conversion_Blocking(const adc_config_t *adc , adc_channel_select_t channel , uint16 *conversion_result);
/**
 * @brief Select the desired channel for conversion and get the analog to digital converted value
 * @param adc pointer to the ADC configurations
 * @param channel
 * @param conversion_result
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType ADC_Start_Conversion_Interrupt(const adc_config_t *adc , adc_channel_select_t channel);

#endif	/* HAL_ADC_H */

