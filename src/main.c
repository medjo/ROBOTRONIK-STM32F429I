#include "main.h"

#include <string.h>

void init_UART_receiver(UART_HandleTypeDef *UART_HandleStructure);
void init_UART_transmitter(UART_HandleTypeDef *UART_HandleStructure);

/* UART handler declaration */
UART_HandleTypeDef	UART_HandleStructure_T;
UART_HandleTypeDef	UART_HandleStructure_R;

uint8_t str[1];



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










void UART4_IRQHandler(void)
{

	HAL_UART_IRQHandler(&UART_HandleStructure_T);
}


void Error_UART(){
	reset_all_led();
	while (1) {
		Delay(500);
		HAL_GPIO_TogglePin(GPIOD, LED_ROUGE);
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	reset_all_led();
	if (str[0] == 'o') {
		set_all_led();
	} else if (str[0] == 'a'){
		HAL_GPIO_WritePin(GPIOD, LED_ORANGE, GPIO_PIN_SET);
	}
	else {
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
	}
	
}





void send_word(UART_HandleTypeDef *UART_HandleStructure, const char *str);

int main(void) {

	init();
	init_GPIO_LED();
	
	//UART_HandleTypeDef	UART_HandleStructure_T;
	//UART_HandleTypeDef	UART_HandleStructure_R;
	/*
		
	
	
	__UART4_CLK_ENABLE();
	
	//Configuration de l'UART d'émission
	UART_HandleStructure_R.Init.BaudRate = 9600;//1;//4095
	UART_HandleStructure_R.Init.WordLength = UART_WORDLENGTH_8B;
	UART_HandleStructure_R.Init.StopBits = UART_STOPBITS_1;
	UART_HandleStructure_R.Init.Parity = UART_PARITY_NONE; //ou UART_PARITY_EVEN ou UART_PARITY_ODD
	UART_HandleStructure_R.Init.Mode = UART_MODE_TX_RX; // ou UART_MODE_RX ou UART_MODE_TX_RX
	UART_HandleStructure_R.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_HandleStructure_R.Init.OverSampling = UART_OVERSAMPLING_8;
	UART_HandleStructure_R.Instance = UART4;
	
	//HAL_UART_Init(UART_HandleStructure);
	if(HAL_UART_Init(&UART_HandleStructure_R) != HAL_OK)
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
	
	*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	str[0] = 'a';
	init_UART_transmitter(&UART_HandleStructure_T);
	//init_UART_receiver(&UART_HandleStructure_R);
	
	
	
	if(HAL_UART_Receive_IT(&UART_HandleStructure_T, str, 1) != HAL_OK)
  {
    Error_UART();
  }
	
	
	
	

	
	
	
	
	
	
	uint32_t preempt;
	uint32_t subpri;
	/*
	HAL_NVIC_GetPriority(SysTick_IRQn, NVIC_PRIORITYGROUP_2, &preempt, &subpri);
	
	preempt += 48;
	subpri += 48;
	send_word(&UART_HandleStructure_T, "\tpreempt : ");
	Delay(50);	
	send_word(&UART_HandleStructure_T, &preempt );
	Delay(50);
	send_word(&UART_HandleStructure_T, "\n");
	Delay(50);
	send_word(&UART_HandleStructure_T, "subpri : ");
	Delay(50);
	send_word(&UART_HandleStructure_T, &subpri );
	Delay(50);
	send_word(&UART_HandleStructure_T, "\n");
	Delay(50);*/
	HAL_GPIO_WritePin(GPIOD, LED_VERTE, GPIO_PIN_SET);
	
	/*
	uint8_t *buf[4];
	
	buf[0] = 'W';
	buf[1] = 'a';
	buf[2] = 'i';
	buf[3] = 't';
	
	
	HAL_GPIO_WritePin(GPIOD, LED_VERTE, GPIO_PIN_SET);
	//HAL_UART_Transmit(&UART_HandleStructure_T, buf, 4, 5000);
*/
	while (1)
	{
		//HAL_UART_Receive_IT(&UART_HandleStructure_R, (uint8_t *)buf, 4);
		//if (buf[0] != 'W') {
		//	while (1) {
				Delay(500);
				HAL_GPIO_TogglePin(GPIOD, LED_BLEUE);
		//	}
		//}
		//Delay(500);
	}
    return 0;
}

void send_word(UART_HandleTypeDef *UART_HandleStructure, const char *str) {

	/*
	int i = 0 ;
	uint8_t size_buffer = strlen(str);
	uint8_t buffer[size_buffer];
	while (i < size_buffer) {
		
	}*/
	if(HAL_UART_Transmit_IT(UART_HandleStructure, (uint8_t *)str, strlen(str)) != HAL_OK)
  {
    Error_UART();
  }
	//HAL_UART_Transmit_IT(UART_HandleStructure, str, strlen(str));
	
}



void init_UART_transmitter(UART_HandleTypeDef *UART_HandleStructure) {
	
	__UART4_CLK_ENABLE();
	
		
	/*##-3- Configure the NVIC for UART ########################################*/
	HAL_NVIC_SetPriority(UART4_IRQn, 4, 4);
	HAL_NVIC_EnableIRQ(UART4_IRQn);
	
	
	//Configuration de l'UART d'émission
	UART_HandleStructure->Init.BaudRate = 9600;//1;//4095
	UART_HandleStructure->Init.WordLength = UART_WORDLENGTH_8B;
	UART_HandleStructure->Init.StopBits = UART_STOPBITS_1;
	UART_HandleStructure->Init.Parity = UART_PARITY_NONE; //ou UART_PARITY_EVEN ou UART_PARITY_ODD
	UART_HandleStructure->Init.Mode = UART_MODE_TX_RX; // ou UART_MODE_RX ou UART_MODE_TX_RX
	UART_HandleStructure->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_HandleStructure->Init.OverSampling = UART_OVERSAMPLING_8;
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

    GPIO_InitStructure_UART.Pin = GPIO_PIN_0|GPIO_PIN_1;
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

}
