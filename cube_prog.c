#include "cube_prog.h"
#include "lcd.h"
#include "ili934x.h"
#include "point.h"
#include <math.h>
#include <avr/interrupt.h>
#include <stdlib.h>

uint16_t t;
int16_t lcdw, lcdh;
point p = {160, 120, 1, BLUE};
point q = {160, 160, 1, GREEN};
/*point q = {140, 120, 1, ORANGE};
point r = {180, 120, 1, ORANGE};
point s = {160, 100, 1, ORANGE};
point u = {160, 140, 1, ORANGE};*/

void main(void) {
	/* 8MHz clock, no prescaling. */
	CLKPR = (1 << CLKPCE);
	CLKPR = 0;

	/* Initialise the LCD display driver */
	init_lcd();
	set_frame_rate_hz(61);

	/* So the compiler doesn't worry about unsigned/signed integer comparisons (can have negative coords). */
	lcdw = (int16_t) display.width;
	lcdh = (int16_t) display.height;

	/* Enable external interrupts, for when pin 6 is changed. For non-flickering display. */
	EIMSK |= _BV(INT6);

	/* Start time. */
	t = 0;

	/* Start loop, with interrupts to update time & animation. */
	sei();
	while(1){}
	cli();
}

void redraw(){
	if(t<display.width){
		/* Clearing. */
		clear_pt2D(&p);
		clear_pt2D(&q);
/*		clear_pt2D(&q);
		clear_pt2D(&r);
		clear_pt2D(&s);
		clear_pt2D(&u);*/

		/* Transforming. */
		updX(&q, 160+30*sin(t));
		rotZ(&p, 1);
/*		rotZ(&q, 1);
		rotZ(&r, 1);
		rotZ(&s, 1);
		rotZ(&u, 1);*/
		point pp = project(&p, 128, 127);				/* Shows weird spiral for dist < fov, dot in centre if >= fov */
/*		point qp = project(&q);
		point rp = project(&r);
		point sp = project(&s);
		point up = project(&u);*/

		/* Redrawing. */
		draw_pt2D(&p);
		draw_pt2D(&q);
		draw_pt2D(&pp);
/*		draw_pt2D(&qp);
		draw_pt2D(&rp);
		draw_pt2D(&sp);
		draw_pt2D(&up);*/
	}else{t = 0;}
}

void draw_px(int16_t x, int16_t y, uint16_t col){
	int16_t fy = lcdh - y;					/* Flip y value, since maths uses y=0 at bottom but lcd uses y=0 at top. */

	if(x >= 0 && x <= lcdw && fy >= 0 && fy <= lcdh){
		write_cmd(PAGE_ADDRESS_SET);		/* Setting maximum & minimum y coordinate to draw. */
		write_data16(fy);
		write_data16(fy);
		write_cmd(COLUMN_ADDRESS_SET);		/* Setting maximum & minimum x coordinate to draw. */
		write_data16(x);
		write_data16(x);
		write_cmd(MEMORY_WRITE);			/* Setting to write memory; ie. to colour the pixel. */
		write_data16(col);
	}
}

void draw_line(int16_t x1, int16_t x2, int16_t y1, int16_t y2, uint16_t col){
/* Uses Bresenham's Line Algorithm, with an implementation adapted from:
   http://www.brackeen.com/vga/shapes.html */
	int16_t fy1 = lcdh - y1;			/* Flip y values, since maths uses y=0 at bottom but lcd uses y=0 at top. */
	int16_t fy2 = lcdh - y2;

	if( (x1 < 0 && x2 < 0) || (fy1 < 0 && fy2 < 0) || 
		(x1 > lcdw && x2 > lcdw) || (fy1 > lcdh && fy2 > lcdh)){}else{
		
		uint16_t i, absDistX, absDistY, x, y, currX, currY;
		int16_t distX, distY, signDX, signDY;

		distX = x2 - x1;				/* x axis distance */
		distY = fy2 - fy1;				/* y axis distance */
		absDistX = abs(distX);			/* Absolute x axis distance */
		absDistY = abs(distY);			/* Absolute y axis distance */
		signDX = sgn(distX);			/* Sign of x axis distance (going left or right) */
		signDY = sgn(distY);			/* Sign of y axis distance (going up or down) */
		x = absDistY>>1;				/* y distance / 2 */
		y = absDistX>>1;				/* x distance / 2 */
		currX = x1;						/* Current x coordinate, to be drawn. */
		currY = fy1;					/* Current y coordinate, to be drawn. */

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

ISR( INT6_vect ){
	t++;
	redraw();
}