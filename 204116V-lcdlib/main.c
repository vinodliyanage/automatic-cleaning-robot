#include <avr/io.h>

#include "lcdlib.h"

int main(void)
{
	LCD_init();
	
	LCD_write_string("MODE:G", 1, 1);
	LCD_write_string("CONTROL:A", 8, 1);
	LCD_write_string("BATTERY: ", 1, 2);
	LCD_write_number(100, 10, 2, 0);
	LCD_write_char('%', 13, 2);
}

