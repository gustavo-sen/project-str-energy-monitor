#pragma once
#include <stdint.h>
#include "stm32f4xx_hal.h"

#define CLEAR_CMD 0x01
#define LCD_SET_CURSOR_CMD 0x80

#define ADDRESS_LCD 0x4E // change this according to ur setup
#define LCD_ROWS    2    // Número de linhas no LCD
#define LCD_COLUMNS 16   // Número de colunas no LCD

void lcd_init (I2C_HandleTypeDef _hi2c);
void lcd_send_string (char *str);
void lcd_send_cmd (char cmd);
void lcd_send_data (char data);
void LCD_set_cursor_pos(uint8_t col, uint8_t row);
void lcd_clear();