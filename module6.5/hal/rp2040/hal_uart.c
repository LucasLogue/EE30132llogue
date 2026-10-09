#include "hal_uart.h"
#include <stdint.h>
#include <stdbool.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
//M6: include irq
#include "hardware/irq.h"

#define GPS_BAUDRATE 38400
#define GPS_RX_PIN 17

//M6: now taking the handler as param
void hal_uart_init(hal_uart_rx_callback_t cb){
    //still need to init uart
    gpio_set_function(GPS_RX_PIN, GPIO_FUNC_UART);
    uart_init(uart0, GPS_BAUDRATE);
    //M6: now adding the vector table entry to handler 
    if(cb != NULL){ //can pass cb as NULL, to tell this function to setup the uart without IRQ
        irq_set_exclusive_handler(UART0_IRQ, cb); //handler installed to IRQ table for UART0
                                                  //notice the HAL keeps no wrapper of its own IRQ table
        irq_set_enabled(UART0_IRQ, true); //the entry alr exists, now the MCU enables it to work
        uart_set_irqs_enabled(uart0, true, false); //enable recieve data available intrpt, disable transmit intrpt 
    } //M6 changes end
}

bool hal_uart_is_readable(void){ //M6: the applications handler will loop on this
                                 //as interrupt is asserted (aka going on) as long as the FIFO of readable bytes
                                 //is not empty, NOT one byte per interrupt
    return uart_is_readable(uart0);
}
char hal_uart_getc(void){
    return uart_getc(uart0);
    // char c = *((volatile uint8_t *)0x40034000); //get volatile memory address pointer
    // return c
}

