/* 
 * File:   hal_gpio.c
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#include "hal_gpio.h"

/*reference to the data direction control registers*/
volatile uint8 *tris_registers[] = {&TRISA ,&TRISB, &TRISC, &TRISD, &TRISE};
/*reference to the data latch register (read and write to data register)*/
volatile uint8 *lat_registers[]  = {&LATA ,&LATB, &LATC, &LATD, &LATE};
/*reference to the port status register*/
volatile uint8 *port_registers[] = {&PORTA ,&PORTB, &PORTC, &PORTD, &PORTE};


/**
 * @brief initialize the direction of a specific pin @ref direction_t
 * @param config Pointer to the configurations  @ref pin_config_t
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t * config){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == config) || (config->pin > PIN_MAX_NUMBER-1)) // validate the pointer and that the user will not choose a pin number higher than 7
    {
        retVal = E_NOT_OK;
    }else{
            switch(config->direction){
        case GPIO_DIRECTION_OUTPUT :
            CLEAR_BIT(*tris_registers[config->port] , config->pin);
            break;
        case GPIO_DIRECTION_INPUT  :
            SET_BIT(*tris_registers[config->port] , config->pin);
            break;
        default : retVal = E_NOT_OK;
    }
        retVal = E_OK;
    }
    return retVal;
}
#endif
/**
 * @brief return the direction of a specific pin
 * @param config Pointer to the configurations  @ref pin_config_t
 * @param direcion_status
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * config , direction_t * direcion_status){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == config) || (NULL == direcion_status) || (config->pin > PIN_MAX_NUMBER-1))
    {
        retVal = E_NOT_OK;
    }else{
       * direcion_status = READ_BIT(*tris_registers[config->port] , config->pin);
       retVal = E_OK;
    }
    return retVal;
} 
#endif
/**
 * @brief write logic to a specific pin to be High or Low
 * @param config Pointer to the configurations  @ref pin_config_t
 * @param logic_status
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t * config , logic_t logic_status){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == config) || (config->pin > PIN_MAX_NUMBER-1))
    {
        retVal = E_NOT_OK;
    }else{
        switch(logic_status){
            case GPIO_LOW:
                CLEAR_BIT(*lat_registers[config->port] , config->pin);
                break;
            case GPIO_HIGH:
                SET_BIT(*lat_registers[config->port] , config->pin);
                break;
            default : retVal = E_OK;
        }
        retVal = E_OK;
    }
    return retVal;
}
#endif
/**
 * @brief Read logic on a specific pin and return it
 * @param config Pointer to the configurations  @ref pin_config_t
 * @param logic_status
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t * config , logic_t *logic_status){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == config) || (NULL == logic_status) || (config->pin > PIN_MAX_NUMBER-1))
    {
        retVal = E_NOT_OK;
    }else{
        *logic_status = READ_BIT(*port_registers[config->port] , config->pin);
        retVal = E_OK;
    }
    return retVal;
}
#endif
/**
 * @brief toggle logic on a specific pin
 * @param config Pointer to the configurations  @ref pin_config_t
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * config){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == config) || (config->pin > PIN_MAX_NUMBER-1))
    {
        retVal = E_NOT_OK;
    }else{
        TOGGLE_BIT(*lat_registers[config->port] , config->pin);
        retVal = E_OK;
    }
    return retVal;
}
#endif
/**
 * @brief To initialize the direction and avoid undefined value to be written in the lat register
 * @param config Pointer to the configurations  @ref pin_config_t
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PIN_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize(const pin_config_t * config){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == config) || (config->pin > PIN_MAX_NUMBER-1))
    {
        retVal = E_NOT_OK;
    }else{
        retVal = gpio_pin_direction_initialize(config);
        retVal = gpio_pin_write_logic(config , config->logic);
        retVal = E_OK;
    }
    return retVal;
}
#endif







/**
 * @brief initialize the direction of a specific port
 * @param port
 * @param direction
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction){
    Std_ReturnType retVal = E_NOT_OK;
    if(port > PORT_MAX_NUMBER - 1){
        retVal = E_NOT_OK;
    }else{
        *tris_registers[port] = direction;
        retVal = E_OK;
    }
    return retVal;
}
#endif
/**
 * @brief return the direction of a specific port
 * @param port
 * @param direction_status
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == direction_status) || (port > PORT_MAX_NUMBER - 1))
    {
        retVal = E_NOT_OK;
    }else{
        *direction_status = *tris_registers[port];
        retVal = E_OK;
    }
    return retVal;
}
#endif
/**
 * @brief write logic to a specific port
 * @param port
 * @param logic
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic){
    Std_ReturnType retVal = E_NOT_OK;
    if(port > PORT_MAX_NUMBER - 1){
        retVal = E_NOT_OK;
    }else{
        *lat_registers[port] = logic;
        retVal = E_OK;
    }
    return retVal;
}
#endif
/**
 * @brief read logic from a specific port
 * @param port
 * @param logic
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == logic) || (port > PORT_MAX_NUMBER - 1))
    {
        retVal = E_NOT_OK;
    }else{
        *logic = *lat_registers[port];
        retVal = E_OK;
    }
    return retVal;
}
#endif
/**
 * @brief toggle logic for a specific port
 * @param port
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port){
    Std_ReturnType retVal = E_NOT_OK;
    if(port > PORT_MAX_NUMBER - 1){
        retVal = E_NOT_OK;
    }else{
        *lat_registers[port] = ~*lat_registers[port];
        retVal = E_OK;
    }
    return retVal;  
}
#endif