#include "error.h"

void mapping_error() {
    while (1) {
        HAL_GPIO_TogglePin(GPIOD, LED_ROUGE);
        Delay(100);
    }
}
