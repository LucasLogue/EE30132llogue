#include <stdio.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"

// pins for white led and reciever GPS uart reciever
//define the baudrate like discrete version of hz
//blinking interval
#define WHITE_LED_PIN 24
#define GPS_UART_RX_PIN 17
#define GPS_BAUDRATE 38400
#define LED_BLINK_PERIOD_US 1000000U

int main(void){
    stdio_init_all(); //USB serial console
    gpio_init(WHITE_LED_PIN); //LED's gpio pin
    gpio_set_dir(WHITE_LED_PIN, true); //set pin to be output
    gpio_put(WHITE_LED_PIN, false); //setting initial state, to me it should be false

    uart_init(uart0, GPS_BAUDRATE); //we have uart0 and uart1 for the pico, we use uart0
    //then set its baudrate
    gpio_set_function(GPS_UART_RX_PIN, GPIO_FUNC_UART); //(uint gpio, gpio_function_t fn)
    //pretty much set the gpio pin, then set it to its respective function "GPIO_FUNC_{Peripheral Type}"

    uint64_t next_blink_us = time_us_64() + LED_BLINK_PERIOD_US; //setting the time at which the next blink should occur

    while(true){
        while(uart_is_readable(uart0)){ //any bytes in uart buffer waiting to be read
            char c = uart_getc(uart0); //uart get character from uart0
            printf("RX: %c\n", c);
        }
        if(time_us_64() >= next_blink_us){
            bool led_state = gpio_get(WHITE_LED_PIN);
            gpio_put(WHITE_LED_PIN, !led_state);
            next_blink_us = time_us_64() + LED_BLINK_PERIOD_US;
        }
    }
}
//it works! just like expected!
