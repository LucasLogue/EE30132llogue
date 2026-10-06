#ifndef HAL_UART_H
#define HAL_UART_H
//remember no MCU specifics in the headers
#include <stdint.h>
#include <stdbool.h>
void hal_uart_init(void);
bool hal_uart_is_readable(void);
char hal_uart_getc(void);

#endif
