#include "lcdlib.h"

void LCD_cmd(unsigned char cmd)
{
	LCD_DATA_PORT = cmd;
	
	REGISTER_SELECT_LOW(); 
	ENABLE_HIGH(); 
	_delay_ms(1);
	ENABLE_LOW();
}

void LCD_init()
{
	LCD_DATA_DDR = 0xff;
	LCD_CONTROL_DDR |= (1 << REGISTER_SELECT) | (1 << ENABLE_SIGNAL);
	
	LCD_cmd(0x38); _delay_ms(2);
	LCD_cmd(0x02); _delay_ms(2);
	LCD_cmd(0x01); _delay_ms(2);
	LCD_cmd(0x0c); _delay_ms(2);
	LCD_cmd(0x06); _delay_ms(2);
	LCD_cmd(0x80); _delay_ms(2);
}

void setPosition(unsigned char pos_x, unsigned char pos_y)
{
	if(pos_x < 1 || pos_x > 16 || pos_y < 1 || pos_y > 2)
	{
		pos_x = 1;
		pos_y = 1;
	}
	
	LCD_cmd(0x3f + pos_x + (pos_y * 64));
}

void LCD_out(char ch)
{
	LCD_DATA_PORT = ch;
	REGISTER_SELECT_HIGH();
	ENABLE_HIGH();
	_delay_ms(1);
	ENABLE_LOW();
}

void LCD_write_char(char ch, unsigned char pos_x, unsigned char pos_y)
{
	setPosition(pos_x, pos_y);
	
	LCD_DATA_PORT = ch;
	REGISTER_SELECT_HIGH();
	ENABLE_HIGH();
    _delay_ms(1);
	ENABLE_LOW();
}

void LCD_write_string(char *st, unsigned char pos_x, unsigned char pos_y)
{
	
	unsigned char i;
	
	setPosition(pos_x, pos_y);
	
	i = 0;
	while(st[i] != '\0')
	{
		LCD_out(st[i]);
		i++;
	}
}

unsigned char LCD_write_number(unsigned char number, unsigned char pos_x, unsigned char pos_y, char zfill)
{
	long temp, i;
	if(number == 0) 
	{
		setPosition(pos_x, pos_y);
		for(i = 0; i<zfill; i++) LCD_out(0x30); // ascii value of 0 = 48(Dec) or 0x30(Hex)
		return 0;
	}
	temp = number % 10;
	LCD_write_number(number / 10, pos_x, pos_y, zfill);
	LCD_out(temp + 48);
	return 0;
}

void LCD_clear()
{
	LCD_cmd(0x01);
	_delay_ms(2);
	LCD_cmd(0x80);
}
