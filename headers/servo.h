#ifndef __SERVO_H__
#define __SERVO_H__

#include "main.h"

#define PIN_OFF 0
#define PIN_ON 1

typedef struct
{

    TIM_HandleTypeDef	TIM_HandleStructure;
    TIM_OC_InitTypeDef	TIM_OC_InitStructure;
    uint32_t			Channel;

} Servo_t;

void set_position_servo(uint32_t angle, Servo_t *servoX);
void init_servo(Servo_t *servoX, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void display_PWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void test_servo(Servo_t *servoX, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif
