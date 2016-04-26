#include "lcd.h"

void main(void) {
	/* Initialise the LCD display driver */
	init_lcd();

	/* INITIAL TEST: RECTANGLE. */
	/* Placeholder rectangle, for testing. Args: left, right, top, bottom. */
	rectangle r = {0, 50, 0, 50};

	/* Drawing the rectangle. Args: Rectangle, colour. */
	fill_rectangle(r, FIRE_BRICK);
}