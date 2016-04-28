#include "lcd.h"
#include "ili934x.h"

void main(void) {
	/* Initialise the LCD display driver */
	init_lcd();

	/* INITIAL TEST: RECTANGLE. */
	/* Placeholder rectangles, for testing. Args: left, right, top, bottom. */
	/*rectangle r1 = {0, 5, 0, 5};*/
	rectangle r2 = {1, 5, 1, 5};

	/* Drawing the rectangles. Args: Rectangle, colour. */
	/*fill_rectangle(r1, BLACK);*/
	fill_rectangle(r2, BLACK);
/*	write_data16(CYAN);
	write_data16(BLUE);
	write_data16(PURPLE);
	write_data16(RED);
	write_data16(ORANGE);
	write_data16(YELLOW);
	write_data16(GREEN_YELLOW);
	write_data16(LIME_GREEN);
	write_data16(GREEN);
	write_data16(TURQUOISE);*/
	write_data16(CYAN);
	write_data16(CYAN);
	write_data16(CYAN);
	write_data16(CYAN);
	write_data16(CYAN);
	write_data16(RED);
	write_data16(RED);
	write_data16(RED);
	write_data16(RED);
	write_data16(RED);
	write_data16(GREEN);
	write_data16(GREEN);
	write_data16(GREEN);
	write_data16(GREEN);
	write_data16(GREEN);
	write_data16(PURPLE);
	write_data16(PURPLE);
	write_data16(PURPLE);
	write_data16(PURPLE);
	write_data16(PURPLE);
	write_data16(YELLOW);
	write_data16(YELLOW);
	write_data16(YELLOW);
	write_data16(YELLOW);
	write_data16(YELLOW);
}