/* 
 * File:   hal_gpio.h
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/***************************************Includes***************************************/

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/***********************************Macro Declarations**********************************/
#define BIT_MASK (uint8)1

#define PORT_MAX_NUMBER 5
#define PIN_MAX_NUMBER  8

#define PORTA_MASK   0xFF
#define PORTB_MASK   0xFF
#define PORTC_MASK   0xFF
#define PORTD_MASK   0xFF
#define PORTE_MASK   0xFF

/******************************Macro Function Declarations******************************/

#define PLATFORM PIC18F
#if PLATFORM == PIC18F
	 #define HWREG(_x)   (*((volatile uint8_t *) (_x)))
#elif PLATFORM == DIS_PIC
	#define HWREG(_x)   (*((volatile uint16_t *) (_x)))
#elif PLATFORM == PIC32
	#define HWREG(_x)   (*((volatile uint32_t *) (_x)))
#else 
	#error "Not Supported Platform"
#endif

#define SET_BIT(REG,BIT_POSN)    (REG |=(BIT_MASK<<BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)  (REG &=~((BIT_MASK<<BIT_POSN)))
#define TOGGLE_BIT(REG,BIT_POSN) (REG ^=(BIT_MASK<<BIT_POSN))
#define READ_BIT(REG,BIT_POSN)   ((REG >> BIT_POSN) & BIT_MASK)

/***********************************Datatype Declarations*******************************/

typedef enum{
    GPIO_LOW=0,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT=0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum{
    GPIO_PIN0=0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;

typedef enum{
    PORTA_INDEX=0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}port_index_t;

typedef struct{
    uint8 port      : 3; /* @ref port_index_t*/
    uint8 pin       : 3; /* @ref pin_index_t*/
    uint8 logic     : 1; /* @ref logic_t*/
    uint8 direction : 1; /* @ref direction_t*/
}pin_config_t;

/***********************************Function Declarations*******************************/

/**
 * @brief initialize the direction of a specific pin @ref direction_t
 * @param config Pointer to the configurations  @ref pin_config_t
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t * config);

/**
 * @brief return the direction of a specific pin
 * @param config Pointer to the configurations  @ref pin_config_t
 * @param direcion_status
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * config , direction_t * direcion_status); // the second parameter is fo the return

/**
 * @brief write logic to a specific pin to be High or Low
 * @param config Pointer to the configurations  @ref pin_config_t
 * @param logic_status
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t * config , logic_t logic_status);

/**
 * @brief Read logic on a specific pin and return it
 * @param config Pointer to the configurations  @ref pin_config_t
 * @param logic_status
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t * config , logic_t *logic_status); //care the * in the second parameter

/**
 * @brief toggle logic on a specific pin
 * @param config Pointer to the configurations  @ref pin_config_t
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * config);

/**
 * @brief To initialize the direction and avoid undefined value to be written in the lat register
 * @param config Pointer to the configurations  @ref pin_config_t
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType gpio_pin_initialize(const pin_config_t * config);



/**
 * @brief initialize the direction of a specific port
 * @param port
 * @param direction
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction);

/**
 * @brief return the direction of a specific port
 * @param port
 * @param direction_status
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status);

/**
 * @brief write logic to a specific port
 * @param port
 * @param logic
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);

/**
 * @brief read logic from a specific port
 * @param port
 * @param logic
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic); //care the * in the second parameter

/**
 * @brief toggle logic for a specific port
 * @param port
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port);

#endif	/* HAL_GPIO_H */

