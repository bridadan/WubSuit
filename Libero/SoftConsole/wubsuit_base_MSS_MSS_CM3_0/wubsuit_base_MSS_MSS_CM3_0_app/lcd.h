#ifndef __LCD_H_
#define __LCD_H_

#include <stdio.h>
#include "drivers/CoreUARTapb/core_uart_apb.h"

#define LCD_LINE_HEIGHT 12
#define LCD_MENU_OPTION_X 15
#define LCD_MENU_VALUE_X 120
#define LCD_VALUE_X 100
#define LCD_TOP_Y 127

void LCD_init(UART_instance_t *inst);
void LCD_drawString(char* str, uint8_t x, uint8_t y);
void LCD_clearScreen();
void LCD_eraseBlock(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

#endif /* __LCD_H_ */
