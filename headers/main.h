#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "stm32f4xx_hal_conf.h"
#include "error.h"
#include "LED.h"
#include "servo.h"

volatile uint32_t time_var1, time_var2;

void Delay(volatile uint32_t nCount);//Delays nCount ms
void init();

#endif
