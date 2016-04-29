#include "cube_prog.h"
#include "lcd.h"
#include "ili934x.h"
#include <stdlib.h>

void main(void) {
	/* Initialise the LCD display driver */
	init_lcd();

	draw_px(50, 50, RED);
	draw_horiz(100, 150, 75, BLUE);
	draw_horiz(150, 100, 100, GREEN);
	draw_line(100, 150, 125, 125, YELLOW);
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
		x = absDistY>>1;				/* Y distance / 2 */
		y = absDistX>>1;
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

/*void draw_line(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t col){
	uint16_t currX, smallX, bigX, currY, smallY, bigY
	float gradient;

	if(x1 <= display.width && x2 <= display.width && y <= display.height){
		if(x1 < x2){
			bigX = x2;
			smallX = x1;
		}else{
			bigX = x1;
			smallX = x2;
		}
		if(y1 < y2){
			bigY = y2;
			smallY = y1;
		}else{
			bigY = y1;
			smallY = y2;
		}

		gradient = (bigY - smallY) / (bigX - smallX);
		if((bigX - smallX) > (bigY - smallY)){
			/* If line is more horizontal than vertical. */

/*		}else{
			/* If line is more vertical than horizontal. */

/*		}
	}
}*/

void draw_horiz(uint16_t x1, uint16_t x2, uint16_t y, uint16_t col){
	uint16_t currX, smallX, bigX;

	if(x1 <= display.width && x2 <= display.width && y <= display.height){
		if(x1 < x2){
			bigX = x2;
			smallX = x1;
		}else{
			bigX = x1;
			smallX = x2;
		}

		write_cmd(PAGE_ADDRESS_SET);
		write_data16(y);
		write_data16(y);
		write_cmd(COLUMN_ADDRESS_SET);
		write_data16(smallX);
		write_data16(bigX);
		write_cmd(MEMORY_WRITE);
		for(currX = smallX; currX <= bigX; currX++){
			write_data16(col);
		}
	}
}