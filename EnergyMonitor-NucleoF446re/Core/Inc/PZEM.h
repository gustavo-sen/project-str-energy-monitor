#ifndef INC_PERIPH_PZEM_H_
#define INC_PERIPH_PZEM_H_
#define SLAVE_ADDR 	0XF8
#include "stm32f4xx.h"

typedef struct
{
	float voltage; 
	float current;
	float frequency;
	float power;

}pzem_values;

void init_pzem(UART_HandleTypeDef _huart);
void get_meter_values(pzem_values *values);

//---------------------------
#endif /* INC_PERIPH_PZEM_H_ */
