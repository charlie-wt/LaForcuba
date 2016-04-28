#include "cube_prog.h"
#include "lcd.h"
#include "ili934x.h"

void main(void) {
	/* Initialise the LCD display driver */
	init_lcd();

	draw_px(50, 50, RED);
	/*draw_px(100, 100);*/
}

void draw_px(uint16_t x, uint16_t y, uint16_t col){
	if(x <= display.width && y <= display.height) {
		write_cmd(PAGE_ADDRESS_SET);
		write_data16(y);
		write_data16(y);
		write_cmd(COLUMN_ADDRESS_SET);
		write_data16(x);
		write_data16(x);
		write_cmd(MEMORY_WRITE);
		write_data16(col);
	}
}

/*void draw_px(uint16_t x, uint16_t y){
	draw_px(x, y, WHITE);
}*/