/* 
 * File:   mcal_layer_initialize.c
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */
#include "mcal_layer_initialize.h"

extern void ADC_DefaultInterruptHandler(void);
extern void Timer0_DefaultInterruptHandler(void);

eusart_t eusart_1 = {
    .EUSART_TxInterruptHandler = NULL,
    .EUSART_RxInterruptHandler = NULL,
    .EUSART_FramingErrorHandler = NULL,
    .EUSART_OverrunErrorHandler = NULL,
    .baudrate = 9600,
    .baudrate_config = BAUDRATE_ASYN_8BIT_lOW_SPEED,
    .eusart_tx_cfg.eusart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE,
    .eusart_tx_cfg.eusart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE,
    .eusart_tx_cfg.eusart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE,
    .eusart_rx_cfg.eusart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE,
    .eusart_rx_cfg.eusart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE,
    .eusart_rx_cfg.eusart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE,
};

//adc_config_t adc_1 = {
//    .ADC_InterruptHandler = ADC_DefaultInterruptHandler,
//    .acquisition_time = ADC_12_TAD,
//    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
//    .adc_channel = ADC_CHANNEL_AN0,
//    .result_format = ADC_RIGHT_FORMAT,
//    .voltage_reference = ADC_VOLTAGE_REF_DISABLE
//};

timer0_t timer0_obj = {
    .TMR0_InterruptHandler = Timer0_DefaultInterruptHandler,
    .operation_mode = TIMER0_TIMER_MODE,
    .register_size = TIMER0_16BIT_REGISTER_MODE,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_16,
    .preload_value = 3036
};


void mcal_layer_initialize(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    
    retVal = EUSART_ASYNC_Init(&eusart_1);
//    retVal = ADC_Init(&adc_1);
    retVal = timer0_initialize(&timer0_obj);
}