#include "main.h"

#include <string.h>

void init_UART_receiver(UART_HandleTypeDef *UART_HandleStructure);
void init_UART_transmitter(UART_HandleTypeDef *UART_HandleStructure);

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




void Error_UART(){
	reset_all_led();
	while (1) {
		Delay(500);
		HAL_GPIO_TogglePin(GPIOD, LED_ROUGE);
	}
}


int main(void) {

	init();
	
	init_GPIO_LED();
	
	
	UART_HandleTypeDef	UART_HandleStructure;
	
	//UART_HandleTypeDef	UART_HandleStructure_R;
	
	//init_UART_transmitter(&UART_HandleStructure_T);
	//init_UART_receiver(&UART_HandleStructure_R);
	__UART4_CLK_ENABLE();
	
	//Configuration de l'UART d'émission
	UART_HandleStructure.Init.BaudRate = 9600;//9600->104µS par bit transmis
	UART_HandleStructure.Init.WordLength = UART_WORDLENGTH_8B;
	UART_HandleStructure.Init.StopBits = UART_STOPBITS_1;
	UART_HandleStructure.Init.Parity = UART_PARITY_NONE; //ou UART_PARITY_EVEN ou UART_PARITY_ODD
	UART_HandleStructure.Init.Mode = UART_MODE_TX_RX; // ou UART_MODE_RX ou UART_MODE_TX_RX
	UART_HandleStructure.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_HandleStructure.Init.OverSampling = UART_OVERSAMPLING_8;
	UART_HandleStructure.Instance = UART4;
	
	//HAL_UART_Init(UART_HandleStructure);
	if(HAL_UART_Init(&UART_HandleStructure) != HAL_OK)
	{
		Error_UART();
	}
	
	
	//AF7 : Pin A0 : USART4_TX
	__GPIOA_CLK_ENABLE();
	
	
	//Configuration du pin de transmission
    GPIO_InitTypeDef GPIO_InitStructure_UART;

    GPIO_InitStructure_UART.Pin = GPIO_PIN_0;
    GPIO_InitStructure_UART.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure_UART.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure_UART.Pull = GPIO_PULLUP;
    GPIO_InitStructure_UART.Alternate = GPIO_AF8_UART4;
    
    //Configure this pin in Alternate function mode
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure_UART);
	
	
	
	uint8_t buf[4];
	buf[0] = 'B';
	buf[1] = 'O';
	buf[2] = '!';
	buf[3] = ' ';
	
	//char *buf = "empty";
	

	//HAL_UART_Receive_IT(&UART_HandleStructure_R, (uint8_t *)buf, strlen(str));
	
	HAL_GPIO_WritePin(GPIOD, LED_VERTE, GPIO_PIN_SET);
	//HAL_UART_Transmit(&UART_HandleStructure_T, buf, 4, 5000);
	
	while (1)
	{
			HAL_UART_Transmit(&UART_HandleStructure, buf, 4, 20);
			Delay(1000);
	}
    return 0;
}

/*
void init_UART_transmitter(UART_HandleTypeDef *UART_HandleStructure) {
	

	//Configuration de l'UART d'émission
	UART_HandleStructure->Init.BaudRate = 9600;//1;//4095
	UART_HandleStructure->Init.WordLength = UART_WORDLENGTH_8B;
	UART_HandleStructure->Init.StopBits = UART_STOPBITS_1;
	UART_HandleStructure->Init.Parity = UART_PARITY_NONE; //ou UART_PARITY_EVEN ou UART_PARITY_ODD
	UART_HandleStructure->Init.Mode = UART_MODE_TX_RX; // ou UART_MODE_RX ou UART_MODE_TX_RX
	UART_HandleStructure->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_HandleStructure->Init.OverSampling = UART_OVERSAMPLING_16;
	UART_HandleStructure->Instance = UART4;
	
	//HAL_UART_Init(UART_HandleStructure);
	if(HAL_UART_Init(UART_HandleStructure) != HAL_OK)
	{
		Error_UART();
	}
	
	
	//AF7 : Pin A0 : USART4_TX
	__GPIOA_CLK_ENABLE();
	
	
	
	//Configuration du pin de transmission
    GPIO_InitTypeDef GPIO_InitStructure_UART;

    GPIO_InitStructure_UART.Pin = GPIO_PIN_0;
    GPIO_InitStructure_UART.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure_UART.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure_UART.Pull = GPIO_PULLUP;
    GPIO_InitStructure_UART.Alternate = GPIO_AF8_UART4;
    
    //Configure this pin in Alternate function mode
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure_UART);
	
	
}

void init_UART_receiver(UART_HandleTypeDef *UART_HandleStructure) {


	
    
	
	//Configuration de l'UART d'émission
	UART_HandleStructure->Init.BaudRate = 9600;
	UART_HandleStructure->Init.WordLength = UART_WORDLENGTH_8B;
	UART_HandleStructure->Init.StopBits = UART_STOPBITS_1;
	UART_HandleStructure->Init.Parity = UART_PARITY_NONE; //ou UART_PARITY_EVEN ou UART_PARITY_ODD
	UART_HandleStructure->Init.Mode = UART_MODE_RX; // ou UART_MODE_RX ou UART_MODE_TX_RX
	UART_HandleStructure->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_HandleStructure->Init.OverSampling = UART_OVERSAMPLING_8;
	UART_HandleStructure->Instance = UART4;
	
	HAL_UART_Init(UART_HandleStructure);
	
	//AF7 : Pin A1 : UART4_RX
	__GPIOA_CLK_ENABLE();
	
	
	//Configuration du pin de transmission
    GPIO_InitTypeDef GPIO_InitStructure_UART;

    GPIO_InitStructure_UART.Pin = GPIO_PIN_1;
    GPIO_InitStructure_UART.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure_UART.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure_UART.Pull = GPIO_PULLUP;
    GPIO_InitStructure_UART.Alternate = GPIO_AF8_UART4;
    
    //Configure this pin in Alternate function mode
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure_UART);

}*/
