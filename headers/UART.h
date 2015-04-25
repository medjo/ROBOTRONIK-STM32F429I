#ifndef __UART_H__
#define __UART_H__

#include "main.h"
void init_UART(UART_HandleTypeDef *UART_HandleStructure);

/* UART handler declarations */
UART_HandleTypeDef	UART_HandleStructure_T;
UART_HandleTypeDef	UART_HandleStructure_R;

UART_HandleTypeDef	UART_Asser_T;
UART_HandleTypeDef	UART_Asser_R;

UART_HandleTypeDef	UART_Xbee_T;
UART_HandleTypeDef	UART_Xbee_R;

void init_UART(UART_HandleTypeDef *UART_HandleStructure);
void send_word(UART_HandleTypeDef *UART_HandleStructure, const char *str);
void send_word_IT(UART_HandleTypeDef *UART_HandleStructure, const char *str);

void test_UART_TX_RX();
void bien_recu ();
void pas_recu ();



uint8_t RX_bfr_test_UART[1];
uint8_t tmp_bfr_test_UART;

#endif
