#include "PWM.h"

void init_PWM() {

    //Configuration des pins
    //TIM3_Ch4 : PC9
    GPIO_InitTypeDef GPIO_InitStructure_PinPWM;
    //Enable the clock for the TIM GPIOs
    __GPIOC_CLK_ENABLE();
    GPIO_InitStructure_PinPWM.Pin = GPIO_PIN_9;
    GPIO_InitStructure_PinPWM.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure_PinPWM.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure_PinPWM.Pull = GPIO_PULLUP;
    GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM3;
    //Configure these TIM pins in Alternate function mode
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure_PinPWM);
    //INITIALISATION du TIMER3
    TIM_HandleTypeDef TIM_HandleStructure;
    TIM_Base_InitTypeDef TIM_Base_InitStructure;
    uint32_t PrescalerValue = 0;
    uint32_t Timer_Frequency = 1000000;
    //TIMER3 Channel 4 is for PWM on PC9
    //Enable the TIM interface clock
    __TIM3_CLK_ENABLE();
    // Compute the prescaler value 
    PrescalerValue = (uint32_t) ((SystemCoreClock /2) / Timer_Frequency) - 1;
    TIM_Base_InitStructure.Prescaler = PrescalerValue;
    TIM_Base_InitStructure.Period = 20000 - 1;
    TIM_Base_InitStructure.CounterMode = TIM_COUNTERMODE_UP;
    TIM_Base_InitStructure.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM_HandleStructure.Instance = TIM3;
    TIM_HandleStructure.Init = TIM_Base_InitStructure;
    TIM_HandleStructure.Channel = HAL_TIM_ACTIVE_CHANNEL_4;
    HAL_TIM_Base_Init(&TIM_HandleStructure);
    //HAL_TIM_Base_Start_IT(&TIM_HandleStructure);
    //INITIALISATION PWM
    TIM_OC_InitTypeDef TIM_OC_InitStructure;
    //PWM mode 1
    TIM_OC_InitStructure.OCMode = TIM_OCMODE_PWM1;
    //Durée de la pulsation
    TIM_OC_InitStructure.Pulse = 1500;
    //Actif à l'état haut
    TIM_OC_InitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
    TIM_OC_InitStructure.OCFastMode = TIM_OCFAST_ENABLE;
    //HAL_TIM_PWM_Init(&TIM_HandleStructure);
    HAL_TIM_PWM_ConfigChannel(&TIM_HandleStructure, &TIM_OC_InitStructure, TIM_CHANNEL_4);
    //Avtication du périphérique timer pour génération de PWM
    HAL_TIM_PWM_Start(&TIM_HandleStructure, TIM_CHANNEL_4);
    HAL_TIM_PWM_Start_IT(&TIM_HandleStructure, TIM_CHANNEL_4);

}
