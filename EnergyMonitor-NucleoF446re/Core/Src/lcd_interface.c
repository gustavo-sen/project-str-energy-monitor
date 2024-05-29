#include "lcd_interface.h"

static uint8_t backlight = 1;
static I2C_HandleTypeDef hi2c1;

void lcd_send_cmd (char cmd){
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data){
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1
	data_t[1] = data_u|0x09;  //en=0, rs=1
	data_t[2] = data_l|0x0D;  //en=1, rs=1
	data_t[3] = data_l|0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit (&hi2c1, ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

/*
*@brief Initialize LCD
*@param I2C HAL I2C_HandleTypeDef
*@return 
*/
void lcd_init (I2C_HandleTypeDef _hi2c){
    hi2c1 = _hi2c;

	// 4 bit initialisation
	HAL_Delay(50);          // wait for >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);           // wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);           // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);    // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

/*
*@brief Send string to LCD Display
*@param string_z
*@return 
*/
void lcd_send_string (const char *str){
	while (*str) lcd_send_data (*str++);
}

void lcd_clear(){
    lcd_send_cmd(CLEAR_CMD);
	HAL_Delay(10);
}

void lcd_set_backligth(uint8_t state){
  if(state) backlight = 1;
  else backlight = 0 ;
}

void lcd_put_cur(int lin, int col) {
    uint8_t addr = 0;
    uint8_t lin_address[4] = {0x00, 0x40, 0x14, 0x54};

    if (LCD_ROWS < lin){
        lin = 0;
	}
    else{
        addr = lin_address[lin];
	}
    addr += col;
    lcd_send_cmd(0x80 | addr);
}


