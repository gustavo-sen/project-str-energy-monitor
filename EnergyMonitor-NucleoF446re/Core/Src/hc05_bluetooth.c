#include "hc05_bluetooth.h"
#include <string.h>

static UART_HandleTypeDef huart;

void hc05_bluetooth_init(UART_HandleTypeDef _huart){
    huart = _huart;
}

void hc05_send_data(const char* pData){
    uint16_t size = strlen(pData);
    HAL_UART_Transmit(&huart, (uint8_t*)pData, size, HAL_MAX_DELAY);
}

void hc05_recieve_data(const char* pData){
    //TODO fazer implementações
    // sugestão, usar DMA em algum caso que nao bloqueia CPU entre outros
}