#ifndef HAL_UART_H
#define HAL_UART_H
//remember no MCU specifics in the headers
#include <stdint.h>
#include <stdbool.h>

//M6: Define new type, a pointer to a no input no output function
typedef void (*hal_uart_rx_callback_t)(void);

//M6: change the init to now take the interrupt handler as arg
//will need to do the 3 hardware steps for a setup, vector table, enable interrupts
//and configure UART periph to raise an IRQ
void hal_uart_init(hal_uart_rx_callback_t cb);
//prev from M5 and before
//void hal_uart_init(void);
bool hal_uart_is_readable(void);
char hal_uart_getc(void);

#endif
