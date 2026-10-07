#include "hal_uart.h"
#include <stdint.h>
#include <stdbool.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"

#define GPS_BAUDRATE 38400
#define GPS_RX_PIN 17

void hal_uart_init(void){
    gpio_set_function(GPS_RX_PIN, GPIO_FUNC_UART);
    uart_init(uart0, GPS_BAUDRATE);
}

bool hal_uart_is_readable(void){
    return uart_is_readable(uart0);
}
char hal_uart_getc(void){
    return uart_getc(uart0);
    // char c = *((volatile uint8_t *)0x40034000); //get volatile memory address pointer
    // return c
}

