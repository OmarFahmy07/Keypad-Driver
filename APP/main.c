#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/Keypad/Keypad_Interface.h"
#include "util/delay.h"

u8 digits [][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
};

int main (void)
{
	LCD_U8Init();
	Keypad_U8Init();
	LCD_U8SendString("Hello");
	LCD_U8SetPosition(LCD_SECOND_ROW, LCD_FIRST_COLUMN);
	LCD_U8SendString("Omar111");
	_delay_ms(1000);
	LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
	LCD_U8SendString("Omar111");
	u8 x, y;

	while (1)
	{
		Keypad_U8GetPressedKey(&x, &y);
		if (x != 100 && y != 100)
		{
			LCD_U8SetPosition(LCD_FIRST_ROW, LCD_FIRST_COLUMN);
			LCD_U8SendNumber(digits[x][y]);
		}
	}

	return 0;
}
