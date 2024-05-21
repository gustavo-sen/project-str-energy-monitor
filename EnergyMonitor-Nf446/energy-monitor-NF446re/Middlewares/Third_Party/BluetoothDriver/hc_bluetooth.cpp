/*
 * hc_bluetooth.cpp
 *
 *  Created on: May 21, 2024
 *      Author: gusta
 */
#include "stm32f4xx_hal_uart.h"
#include <stdint.h>

#define BUFFER_LEN  1

uint8_t RX_BUFFER[BUFFER_LEN] = {0};

UART_HandleTypeDef huart3;

void init_hc05(){

}

/*
 * @breaf check if HC-05 is connected
 * @return 1 if its working
 */
int check_bl_con(){

}

void send_uart(const char* msg){
	HAL_UART_Transmit_IT(&huart3, msg, sizeof(msg));
}

char uart_get_char(char* msg){
	const int timeout = 300;
	HAL_UART_Receive(&huart3, msg, BUFFER_LEN, timeout);
}
