#ifndef HAL_GPIO_H
#define HAL_GPIO_H
#include <stdbool.h>

typedef enum{
    HAL_GPIO_WHITE_LED = 0,
    HAL_GPIO_RED_LED,
    HAL_GPIO_NUM
} hal_gpio_id_t;

/// @brief initializes gpio to default (low)
/// @param id which gpio instance to init
void hal_gpio_init(hal_gpio_id_t id);

/// @brief set the value of gpio instance 
/// @param id which gpio
/// @param value value to set gpio to (true for high, false for low)
void hal_gpio_set(hal_gpio_id_t id, bool value);

/// @brief Gets the value of the specified GPIO instance
/// @param id Which GPIO instance 
/// @return The value of gpio instance (true->high)
bool hal_gpio_get(hal_gpio_id_t id);

#endif
