#ifndef UART_RELAY_H
#define UART_RELAY_H
#include <stdint.h>
#include "hal_gpio.h"
#include "hal_uart.h"
typedef struct {
    hal_gpio_id_t heartbeat; //time interval led
    hal_gpio_id_t activity; //event occurence led
    uint32_t period_ms; //time interval
    uint32_t activity_idle_ms; //time window where activity led on
} uart_relay_config_t;
void uart_relay_run(void); //M6: POTENTIAL ERROR FROM TEXTBOOK
//void uart_relay_run(const uart_relay_config_t *cfg);
#endif
