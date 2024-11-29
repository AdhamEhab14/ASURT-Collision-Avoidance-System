/* 
 * File:   ecu_led.h
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */


#ifndef ECU_LED_H
#define	ECU_LED_H

/****************************************Includes***************************************/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/***********************************Macro Declarations**********************************/

/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

typedef enum{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port       : 3;
    uint8 pin        : 3;
    uint8 led_status : 1;
    uint8 reserved   : 1; // not used yet
}led_t;

/***********************************Function Declarations*******************************/


/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the led off
 * @param led pointer to the led module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType led_initialize(const led_t * led);
/**
 * @brief turn the led on
 * @param led pointer to the led module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType led_turn_on(const led_t * led);
/**
 * @brief turn the led off
 * @param led pointer to the led module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType led_turn_off(const led_t * led);
/**
 * @brief toggle the led
 * @param led pointer to the led module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType led_toggle(const led_t * led);
        

#endif	/* ECU_LED_H */

