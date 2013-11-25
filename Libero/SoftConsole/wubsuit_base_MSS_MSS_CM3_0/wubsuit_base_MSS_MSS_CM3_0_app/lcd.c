#include <inttypes.h>
#include <stdio.h>

uint8_t LCD_selectorPosition = 0;

void LCD_setSelectorPosition(uint8_t position) {
	printf("LCD selector pos: (%u, %u)\n\r", LCD_selectorPosition, position);
	LCD_selectorPosition = position;
}

void LCD_drawString(char* str, uint8_t x, uint8_t y) {
	printf("%s --- (%u, %u)\n\r", str, x, y);
}

void LCD_clearScreen() {
	printf("\n\r*** Screen Cleared ***\n\r");
}
