#pragma once
#include <stdint.h>
#include "stm32f4xx_hal.h"

void hc05_bluetooth_init(UART_HandleTypeDef _huart);
void hc05_send_data(const char* pData);