// now handled in project libraries
//#include <stdio.h>
//#include <stdint.h>

#include "pico/stdlib.h"


// now handled in project libraries
//#include "hardware/gpio.h"
//#include "hardware/uart.h"

//project imports
#include "hal_gpio.h"
//timer used by lib modules and uart used by uart_relay
//#include "hal_timer.h"
//#include "hal_uart.h"

#include "uart_relay.h"

// pins for white led and reciever GPS uart reciever
//define the baudrate like discrete version of hz
//blinking interval
//#define WHITE_LED_PIN 24 //now set in hal_gpio.c

//now defined in uart_relay and hal_uart
/* #define GPS_UART_RX_PIN 17 */
/* #define GPS_BAUDRATE 38400 */
/* #define LED_BLINK_PERIOD_US 1000000U */

int main(void){
    stdio_init_all(); //USB serial console
    //must now initialize that cfg block thing
    uart_relay_config_t cfg = {
        .heartbeat = HAL_GPIO_WHITE_LED,
        .activity = HAL_GPIO_RED_LED,
        .period_ms = 1000,
        .activity_idle_ms = 100,
    };
    // using HAL_GPIO declared variables, and redefining the intervals

    //calling the infinite loop that used to be here, now in uart_relay
    uart_relay_run(&cfg);
}


    //NOW HANDLED BY HAL_GPIO.H
//    hal_gpio_init(HAL_GPIO_WHITE_LED); //LED's gpio pin
 //   hal_gpio_set(HAL_GPIO_WHITE_LED, true); //set pin to be output

    // NOW HANDLED BY hal_uart.h
  //  uart_init(uart0, GPS_BAUDRATE); //we have uart0 and uart1 for the pico, we use uart0
    //then set its baudrate
   // gpio_set_function(GPS_UART_RX_PIN, GPIO_FUNC_UART); //(uint gpio, gpio_function_t fn)
    //pretty much set the gpio pin, then set it to its respective function "GPIO_FUNC_{Peripheral Type}"

    //NOW HANDLED in uart_relay
    //uint64_t next_blink_us = time_us_64() + LED_BLINK_PERIOD_US; //setting the time at which the next blink should occur

    //NOW HANDLED BY uart_relay
    /* while(true){ */
    /*     while(uart_is_readable(uart0)){ //any bytes in uart buffer waiting to be read */
    /*         char c = uart_getc(uart0); //uart get character from uart0 */
    /*         printf("RX: %c\n", c); */
    /*     } */
    /*     if(time_us_64() >= next_blink_us){ */
    /*         bool led_state = hal_gpio_get(HAL_GPIO_WHITE_LED); */
    /*         hal_gpio_set(HAL_GPIO_WHITE_LED, !led_state); */
    /*         next_blink_us = time_us_64() + LED_BLINK_PERIOD_US; */
    /*     } */
    /* } */
//}
//it works! just like expected!
