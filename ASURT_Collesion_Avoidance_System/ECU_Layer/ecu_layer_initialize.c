/* 
 * File:   ecu_layer_initialize.c
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#include "ecu_layer_initialize.h"

led_t led_1 = {
  .port = PORTD_INDEX,
  .pin = GPIO_PIN0,
  .led_status = LED_OFF,
};
pin_config_t buzzer = {
  .port = PORTC_INDEX,
  .pin = GPIO_PIN2,
  .direction = GPIO_DIRECTION_OUTPUT,
  .logic = GPIO_LOW
};


void ecu_layer_initialize(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    retVal = led_initialize(&led_1);
    retVal = gpio_pin_initialize(&buzzer);
}

