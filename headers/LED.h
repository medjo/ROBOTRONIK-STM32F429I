#ifndef __LED_H__
#define __LED_H__

#include "main.h"

#define LED_VERTE GPIO_PIN_12
#define LED_ORANGE GPIO_PIN_13
#define LED_ROUGE GPIO_PIN_14
#define LED_BLEUE GPIO_PIN_15

#define LED_DEBUG_1 GPIO_PIN_12
#define LED_DEBUG_2 GPIO_PIN_13
#define LED_DEBUG_3 GPIO_PIN_14
#define LED_DEBUG_4 GPIO_PIN_15

void test_led();
void reset_all_led();
void set_all_led();
void init_GPIO_LED();

void init_LED_debug();

#endif
