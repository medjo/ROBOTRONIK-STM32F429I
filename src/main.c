#include "main.h"




















/*
 * Called from systick handler
 */
void timing_handler() {
    if (time_var1) {
        time_var1--;
    }
    time_var2++;
}

/*
 * Delay a number of systick cycles (1ms)
 */
void Delay(volatile uint32_t nCount) {
    time_var1 = nCount;

    while(time_var1){};
}

void SysTick_Handler(void)
{
    timing_handler();
}










int main(void) {


    init();
    init_GPIO_LED();

    Servo_t servo1;
    init_servo(&servo1, GPIOC, GPIO_PIN_9);
    set_position_servo(1500, &servo1);
    Delay(1000);
    set_position_servo(1900, &servo1);
    Delay(1000);
    set_position_servo(2000, &servo1);
    Delay(1000);
    set_position_servo(2100, &servo1);
    Delay(1000);
    set_position_servo(2200, &servo1);
    Delay(1000);
    /*
    set_position_servo(800, &servo1);
    Delay(1000);
    set_position_servo(500, &servo1);
    Delay(1000);

    set_position_servo(700, &servo1);
    Delay(1000);
    set_position_servo(1500, &servo1);
    Delay(1000);
    set_position_servo(2500, &servo1);
    Delay(1000);
    
    set_position_servo(2700, &servo1);
    Delay(1000);
    
    set_position_servo(2400, &servo1);
    Delay(1000);
    set_position_servo(1500, &servo1);
    Delay(1000);*/
    
    /*
    while(1){
    	display_PWM(GPIOC, GPIO_PIN_9);
    }*/
    
    /*test_servo(&servo1, GPIOC, GPIO_PIN_9);*/





    return 0;
}


