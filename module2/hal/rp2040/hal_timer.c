#include "pico/stdlib.h"
#include "hal_timer.h"
#include <stdint.h>

uint64_t hal_timer_get_time_us(void){
    return time_us_64();
}
