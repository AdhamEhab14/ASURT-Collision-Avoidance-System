/* 
 * File:   hal_eusart.h
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#ifndef HAL_EUSART_H
#define	HAL_EUSART_H

/***************************************Includes***************************************/

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "hal_eusart_cfg.h"

/***********************************Macro Declarations**********************************/

/* Enable / Disable EUSART Module */
#define EUSART_MODULE_ENABLE   1
#define EUSART_MODULE_DISABLE  0
/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE  		1
#define EUSART_ASYNCHRONOUS_MODE 		0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED  	0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN  		1
#define EUSART_8BIT_BAUDRATE_GEN  		0

/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_TX_DISABLE  0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE  0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE  0

/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_RX_DISABLE  0
/* EUSART Receiver Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE  0
/* EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE  0

/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0

/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

typedef enum{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;

typedef struct{
    interrupt_priority_cfg eusart_tx_interrupt_priority;
	uint8 eusart_tx_enable : 1;
	uint8 eusart_tx_interrupt_enable : 1;
	uint8 eusart_tx_9bit_enable : 1;
    uint8 eusart_tx_reserved : 5;
}eusart_tx_cfg_t;

typedef struct{
    interrupt_priority_cfg eusart_rx_interrupt_priority;
	uint8 eusart_rx_enable : 1;
	uint8 eusart_rx_interrupt_enable : 1;
	uint8 eusart_rx_9bit_enable : 1;
    uint8 eusart_rx_reserved : 5;
}eusart_rx_cfg_t;

typedef union{
	struct{
		uint8 eusart_tx_reserved : 6;
		uint8 eusart_ferr : 1;
		uint8 eusart_oerr : 1;
	};
	uint8 status;
}eusart_error_status_t;

typedef struct{
    uint32 baudrate;
    baudrate_gen_t baudrate_config;
    eusart_tx_cfg_t eusart_tx_cfg;
	eusart_rx_cfg_t eusart_rx_cfg;
	eusart_error_status_t error_status;
	void (*EUSART_TxInterruptHandler)(void);
    void (*EUSART_RxInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
}eusart_t;

/***********************************Function Declarations*******************************/

/**
 * @brief Initialize EUSART module
 * @param _eusart_obj pointer to the EUSART module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Init(const eusart_t *_eusart_obj);
/**
 * @brief DeInitialize EUSART module
 * @param _eusart_obj pointer to the EUSART module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_DeInit(const eusart_t *_eusart_obj);


/**
 * @brief Reading a byte by blocking the CPU till the byte is read
 * @param _eusart_obj pointer to the EUSART module configurations
 * @param _data
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Read_Byte_Blocking(const eusart_t *_eusart_obj , uint8 *_data);
/**
 * @brief Reading a byte without blocking the CPU till the byte is read
 * @param _eusart_obj pointer to the EUSART module configurations
 * @param _data
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Read_Byte_Non_Blocking(const eusart_t *_eusart_obj , uint8 *_data);
/**
 * @brief Restarting Rx by enabling and disabling CREN bit
 * @param _eusart_obj pointer to the EUSART module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_RX_Restart(const eusart_t *_eusart_obj);


/**
 * @brief Writing a byte by blocking the CPU till the byte is written
 * @param _eusart_obj pointer to the EUSART module configurations
 * @param _data
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Write_Byte_Blocking(const eusart_t *_eusart_obj , uint8 _data);
/**
 * @brief Writing a string by blocking the CPU till the byte is written
 * @param _eusart_obj pointer to the EUSART module configurations
 * @param _data
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Write_String_Blocking(const eusart_t *_eusart_obj , uint8 *_data , uint32 _str_length);
/**
 * @brief Writing a byte without blocking the CPU till the byte is written
 * @param _eusart_obj pointer to the EUSART module configurations
 * @param _data
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Write_Byte_Non_Blocking(const eusart_t *_eusart_obj , uint8 _data);
/**
 * @brief Writing a string without blocking the CPU till the byte is written
 * @param _eusart_obj pointer to the EUSART module configurations
 * @param _data
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType EUSART_ASYNC_Write_String_Non_Blocking(const eusart_t *_eusart_obj , uint8 *_data , uint32 _str_length);

#endif	/* HAL_EUSART_H */

