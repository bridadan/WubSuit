#ifndef __LCD_H_
#define __LCD_H_

#include <stdio.h>

#define LCD_LINE_HEIGHT 8
#define LCD_MENU_OPTION_X 10
#define LCD_MENU_VALUE_X 100
#define LCD_VALUE_X 80

void LCD_setSelectorPosition(uint8_t position);
void LCD_drawString(char* str, uint8_t x, uint8_t y);
void LCD_clearScreen();

#endif /* __LCD_H_ */
