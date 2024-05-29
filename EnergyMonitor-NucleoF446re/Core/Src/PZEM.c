/*
 * PZEM.c
 *
 *  Created on: 21 de mai de 2024
 *      Author: rafae
 */
#include "PZEM.h"
#include "main.h"

uint8_t buf[8]={0xF8,0x04,0x00,0x00,0x00,0x0A,0x64,0x64};
uint8_t rst_buf[4]={0xF8, 0x42,0xC2,0X41};
uint8_t res_buf[25];

static UART_HandleTypeDef huart;

void init_pzem(UART_HandleTypeDef _huart){
	huart = _huart;
}

void get_meter_values(pzem_values *values)
{
	HAL_UART_Transmit(&huart,(uint8_t*) &buf, 8, 20);
	HAL_UART_Receive(&huart, res_buf, 25, 250);

	values->voltage		= ((uint32_t) res_buf[3]<< 8 | (uint32_t) res_buf[4]);
	values->current		= ((uint32_t) res_buf[5]<<8  | (uint32_t)res_buf[6]  
						| (uint32_t)res_buf[7]<<24   |(uint32_t)res_buf[8]<<16);

	values->power		= ((uint32_t) res_buf[9]<<8  
						| (uint32_t)res_buf[10] 	 | (uint32_t)res_buf[11]<<24 
						|(uint32_t)res_buf[12]<<16);
						
	values->frequency	= ((uint32_t) res_buf[17]<<8 | (uint32_t)res_buf[18]);
}
