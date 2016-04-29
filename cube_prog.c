#include "cube_prog.h"
#include "lcd.h"
#include "ili934x.h"
#include <stdlib.h>

void main(void) {
	/* Initialise the LCD display driver */
	init_lcd();

	draw_px(50, 50, RED);
	draw_line(100, 150, 75, 75, YELLOW);
	draw_line(100, 150, 100, 125, PURPLE);
	draw_line(150, 100, 150, 125, ORANGE);
}

void draw_px(uint16_t x, uint16_t y, uint16_t col){
	if(x <= display.width && y <= display.height){
		write_cmd(PAGE_ADDRESS_SET);		/* Setting maximum & minimum y coordinate to draw. */
		write_data16(y);
		write_data16(y);
		write_cmd(COLUMN_ADDRESS_SET);		/* Setting maximum & minimum x coordinate to draw. */
		write_data16(x);
		write_data16(x);
		write_cmd(MEMORY_WRITE);			/* Setting to write memory; ie. to colour the pixel. */
		write_data16(col);
	}
}

void draw_line(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t col){
	uint16_t i, absDistX, absDistY, x, y, currX, currY;
	int distX, distY, signDX, signDY;

	if(x1 <= display.width && x2 <= display.width && y1 <= display.height && y2 <= display.height){
		distX = x2 - x1;				/* x axis distance */
		distY = y2 - y1;				/* y axis distance */
		absDistX = abs(distX);			/* Absolute x axis distance */
		absDistY = abs(distY);			/* Absolute y axis distance */
		signDX = sgn(distX);			/* Sign of x axis distance (going left or right) */
		signDY = sgn(distY);			/* Sign of y axis distance (going up or down) */
		x = absDistY>>1;				/* y distance / 2 */
		y = absDistX>>1;				/* x distance / 2 */
		currX = x1;						/* Current x coordinate, to be drawn. */
		currY = y1;						/* Current y coordinate, to be drawn. */

		if(absDistX >= absDistY){		/* If line is more horizontal than vertical */
			for(i=0;i<absDistX;i++){
				y += absDistY;
				if(y >= absDistX){
					y -= absDistX;
					currY += signDY;
				}
				currX += signDX;		/* Simply increment (or decrement) the current x value. */
				draw_px(currX, currY, col);
			}
		}else{							/* If line is more vertical than horizontal */
			for(i=0;i<absDistY;i++){
				x += absDistX;
				if(x >= absDistY){
					x -= absDistY;
					currX += signDX;
				}
				currY += signDY;		/* Simply increment (or decrement) the current y value. */
				draw_px(currX,currY,col);
			}
		}
	}
}