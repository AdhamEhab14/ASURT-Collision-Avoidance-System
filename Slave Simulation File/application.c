/* 
 * File:   application.c
 * Author: Adham Ehab Saleh
 * Submitted to : ASU Racing Team
 * Created on September 26, 2024, 7:16 PM
 */

#include "application.h"

volatile uint8 uart_received_data;

int main() {
    Std_ReturnType retVal = E_NOT_OK; //fixed
    application_initialize(); //fixed

    while(1){
        /*-------------------- Slave Code -----------------------*/
        /* UART Receiving Data */
        retVal = EUSART_ASYNC_Read_Byte_Blocking(&eusart_1 , &uart_received_data);
        retVal = timer0_write_value(&timer0_obj, (3036 + ((50 - uart_received_data) * 1250)));
    }

    return (EXIT_SUCCESS);
}

void Timer0_DefaultInterruptHandler(void){
    if(50 >= uart_received_data){
        led_toggle(&led_1);
        gpio_pin_toggle_logic(&buzzer);
    }
    else{
        led_turn_off(&led_1);
        gpio_pin_write_logic(&buzzer , GPIO_LOW);
    }
}

void application_initialize(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    ecu_layer_initialize(); //fixed 
    mcal_layer_initialize(); //fixed
}
