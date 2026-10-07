#include "uart_relay.h"
#include <stdio.h>
#include "hal_timer.h"
#include "hal_gpio.h"
#include "hal_uart.h"

//typedef struct {
//    hal_gpio_id_t heartbeat; //time interval led
//    hal_gpio_id_t activity; //event occurence led
//    uint32_t period_ms; //time interval
//    uint32_t activity_idle_ms; //time window where activity led on
//} uart_relay_config_t;
//
void uart_relay_run(const uart_relay_config_t *cfg){
    hal_gpio_init(cfg->heartbeat);
    hal_gpio_init(cfg->activity);
    // initialize the heartbeat and activity leds
    // presumably heartbeat = HAL_WHITE_LED and the RED led somewhere

    hal_uart_init();

    uint64_t next_us = hal_timer_get_time_us() + (uint64_t)cfg->period_ms * 1000;
    uint64_t activity_until_us = hal_timer_get_time_us() + (uint64_t)cfg->activity_idle_ms * 1000;
    //scale 32 bit ms values to 64bit microsecs
   
    while(true){ //essentially 
        while(hal_uart_is_readable()){
            putchar(hal_uart_getc()); //put the char into the stdout
            hal_gpio_set(cfg->activity, true); //set activity led on
            activity_until_us = hal_timer_get_time_us() + (uint64_t)cfg->activity_idle_ms * 1000;
        }
        if(hal_timer_get_time_us() >= activity_until_us){
            hal_gpio_set(cfg->activity, false);
        }
        if(hal_timer_get_time_us() >= next_us){
            bool h_state = hal_gpio_get(cfg->heartbeat);
            hal_gpio_set(cfg->heartbeat, !h_state);
            next_us = hal_timer_get_time_us() + (uint64_t)cfg->period_ms * 1000U;
        }
    }
}


