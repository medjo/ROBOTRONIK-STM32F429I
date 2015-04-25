#include "LED.h"

void test_led() {

    HAL_GPIO_TogglePin(GPIOD, LED_ROUGE);
    Delay(500);
    HAL_GPIO_TogglePin(GPIOD, LED_BLEUE);
    Delay(500);
    HAL_GPIO_TogglePin(GPIOD, LED_VERTE);
    Delay(500);
    HAL_GPIO_TogglePin(GPIOD, LED_ORANGE);
    Delay(500);
    reset_all_led();

}

void reset_all_led() {
    HAL_GPIO_WritePin(GPIOD, LED_BLEUE, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, LED_VERTE, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, LED_ORANGE, GPIO_PIN_RESET);
}

void set_all_led() {
    HAL_GPIO_WritePin(GPIOD, LED_BLEUE, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, LED_VERTE, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, LED_ORANGE, GPIO_PIN_SET);
}

void init_GPIO_LED() {

    GPIO_InitTypeDef  GPIO_InitStructure;
    // GPIOD Periph clock enable
    __GPIOD_CLK_ENABLE();

    // Configure PD12, PD13, PD14 and PD15 in output pushpull mode
    GPIO_InitStructure.Pin = GPIO_PIN_12 | GPIO_PIN_13| GPIO_PIN_14| GPIO_PIN_15;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
}

//Initialisation des LED de debug de la sous carte
void init_LED_debug() {

    GPIO_InitTypeDef  GPIO_InitStructure;
    // GPIOD Periph clock enable
    __GPIOB_CLK_ENABLE();

    // Configure PD12, PD13, PD14 and PD15 in output pushpull mode
    GPIO_InitStructure.Pin = GPIO_PIN_12 | GPIO_PIN_13| GPIO_PIN_14| GPIO_PIN_15;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
}
