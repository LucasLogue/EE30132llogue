#include "hal_gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include "hardware/gpio.h"

//NOW WE DECLARE our pin setup
#define WHITE_LED_PIN 24
#define RED_LED_PIN 23

static const uint32_t pin[HAL_GPIO_NUM] = {
    [HAL_GPIO_WHITE_LED] = WHITE_LED_PIN,
    [HAL_GPIO_RED_LED] = RED_LED_PIN,
};
//Now when writing the code, if we assume a pin is passed
//now as the string name for the pin, we must access the corresponding
//pin number we define here

void hal_gpio_init(hal_gpio_id_t id){
    //guard if trying to access outside of array range
    if(id >= HAL_GPIO_NUM){ return; }
    gpio_init(pin[id]);
    gpio_set_dir(pin[id], GPIO_OUT);
    gpio_put(pin[id], false);
}
bool hal_gpio_get(hal_gpio_id_t id){
    if(id >= HAL_GPIO_NUM){ return false; }
    return gpio_get(pin[id]);
}
void hal_gpio_set(hal_gpio_id_t id, bool value){
    if(id >= HAL_GPIO_NUM){ return; }
    gpio_put(pin[id], value);
}

