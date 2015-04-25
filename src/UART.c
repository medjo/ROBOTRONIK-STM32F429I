#include <UART.h>
#include <string.h>

void USART3_IRQHandler(void)//cf. startup_stm32f407xx.s
{
	HAL_UART_IRQHandler(&UART_Asser);
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

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	tmp_bfr_test_UART = *RX_bfr_test_UART;
}

//void UART_handler_

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	reset_all_led();
	if (*RX_bfr_test_UART == tmp_bfr_test_UART) {
		bien_recu ();
	} else {
		pas_recu ();
	}
}

void bien_recu () {
	if(HAL_UART_Transmit(&UART_HandleStructure_T, ".\n\rBien reçu la lettre ", 24, 20) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
  	}
  	if(HAL_UART_Transmit(&UART_HandleStructure_T, RX_bfr_test_UART, 1, 20) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
  	}
  	if(HAL_UART_Transmit(&UART_HandleStructure_T, "\n\n\rDemande la lettre ", 21, 20) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
  	}
  	*RX_bfr_test_UART += 1;
  	tmp_bfr_test_UART = *RX_bfr_test_UART;
  	if(HAL_UART_Transmit(&UART_HandleStructure_T, RX_bfr_test_UART, 1, 20) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
  	}
  	if(HAL_UART_Receive_IT(&UART_HandleStructure_T, RX_bfr_test_UART, 1) != HAL_OK)
	{
	HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
	}
} 

void pas_recu () {
	if(HAL_UART_Transmit(&UART_HandleStructure_T, ".\n\rJe n'ai pas reçu la lettre ", 31, 20) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
	}
	if(HAL_UART_Transmit(&UART_HandleStructure_T, &tmp_bfr_test_UART, 1, 20) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
	}
	if(HAL_UART_Transmit(&UART_HandleStructure_T, ". Mais j'ai reçu la lettre ", 28, 20) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
	}
	if(HAL_UART_Transmit(&UART_HandleStructure_T, RX_bfr_test_UART, 1, 20) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
	}
	if(HAL_UART_Transmit(&UART_HandleStructure_T, "\n\n\rDemande la lettre ", 21, 20) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
	}
	if(HAL_UART_Transmit(&UART_HandleStructure_T, &tmp_bfr_test_UART, 1, 20) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
	}
	if(HAL_UART_Receive_IT(&UART_HandleStructure_T, RX_bfr_test_UART, 1) != HAL_OK)
	{
	HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
	}
}

void send_word(UART_HandleTypeDef *UART_HandleStructure, const char *RX_bfr_test_UART) {

	if(HAL_UART_Transmit(UART_HandleStructure, (uint8_t *)RX_bfr_test_UART, strlen(RX_bfr_test_UART), 20) != HAL_OK)
  {
    Error_UART();
  }
}

void send_word_IT(UART_HandleTypeDef *UART_HandleStructure, const char *RX_bfr_test_UART) {

	if(HAL_UART_Transmit_IT(UART_HandleStructure, (uint8_t *)RX_bfr_test_UART, strlen(RX_bfr_test_UART)) != HAL_OK)
	{
	Error_UART();
	}
}



void init_UART(UART_HandleTypeDef *UART_HandleStructure) {
	
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

/*
	Programme de test de l'UART en réception et en transmission à l'aide d'un bus pirate
	
	Relier : 
		- la masse du STM32 à celle du bus pirate
		- le pin PA0 à RX du bus pirate
		- le pin PA1 à TX du bus pirate
		
	Connecter le bus pirate au pc.
	Lancer picocom /dev/ttyUSB0
	Mettre le programme sur le STM32 (ou faire un reset si il y est déjà
	Et écrire les lettres demandées.
	
	Note : Dans le programme, penser à initialiser les LED
*/
void test_UART_TX_RX(){
	init();
	init_GPIO_LED();
	
	RX_bfr_test_UART[0] = 'a';
	init_UART(&UART_HandleStructure_T);
	
	send_word_IT(&UART_HandleStructure_T, "\n\n\rDemande la lettre ");
	Delay(50);
	send_word_IT(&UART_HandleStructure_T, (const char *)RX_bfr_test_UART);
	if(HAL_UART_Receive_IT(&UART_HandleStructure_T, RX_bfr_test_UART, 1) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
	}

	HAL_GPIO_WritePin(GPIOD, LED_VERTE, GPIO_PIN_SET);
	while (1)
	{
		Delay(500);
		HAL_GPIO_TogglePin(GPIOD, LED_BLEUE);
	}
}

void init_UART_Asser(UART_HandleTypeDef *UART_HandleStructure) {
	
	__USART3_CLK_ENABLE(); //cf. stm32f4xx_hal_rcc_ex.h
	
		
	//##-3- Configure the NVIC for UART ########################################
	HAL_NVIC_SetPriority(USART3_IRQn, 4, 4);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
	
	
	//Configuration de l'UART d'émission
	UART_HandleStructure->Init.BaudRate = 9600;//1;//4095
	UART_HandleStructure->Init.WordLength = UART_WORDLENGTH_8B;
	UART_HandleStructure->Init.StopBits = UART_STOPBITS_1;
	UART_HandleStructure->Init.Parity = UART_PARITY_NONE; //ou UART_PARITY_EVEN ou UART_PARITY_ODD
	UART_HandleStructure->Init.Mode = UART_MODE_TX_RX; // ou UART_MODE_RX ou UART_MODE_TX_RX
	UART_HandleStructure->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_HandleStructure->Init.OverSampling = UART_OVERSAMPLING_8;
	UART_HandleStructure->Instance = USART3; // cf. stm32f407xx.h
	
	
	
	//HAL_UART_Init(UART_HandleStructure);
	if(HAL_UART_Init(UART_HandleStructure) != HAL_OK)
	{
		Error_UART();
	}
	
	
	//AF7 : Pin D8 : USART3_TX
	__GPIOD_CLK_ENABLE();
	
	
	//Configuration du pin de transmission
    GPIO_InitTypeDef GPIO_InitStructure_UART;

    GPIO_InitStructure_UART.Pin = GPIO_PIN_8|GPIO_PIN_8;
    GPIO_InitStructure_UART.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure_UART.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure_UART.Pull = GPIO_PULLUP;
    GPIO_InitStructure_UART.Alternate = GPIO_AF7_USART3;//cf. stm32f4xx_hal_gpio_ex.h
    
    //Configure this pin in Alternate function mode
    HAL_GPIO_Init(GPIOD, &GPIO_InitStructure_UART);
	
}
