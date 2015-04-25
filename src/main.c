#include "main.h"

#include <string.h>





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
	/*init();
	init_GPIO_LED();
	init_LED_debug();*/
	test_UART_TX_RX();
	int i;

	//test_UART_TX_RX();
    return 0;
}


