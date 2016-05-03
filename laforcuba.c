#include "laforcuba.h"
#include "lcd.h"
#include "ili934x.h"
#include "point.h"
#include <math.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

uint16_t t;
int16_t lcdw, lcdh;
point p = {-50, -50, -50, -50, -50, -50, WHITE};
point q = {-50, 50, -50, -50, 50, -50, WHITE};
point r = {50, 50, -50, 50, 50, -50, WHITE};
point s = {50, -50, -50, 50, -50, -50, WHITE};
point a = {-50, -50, 50, -50, -50, 50, WHITE};
point b = {-50, 50, 50, -50, 50, 50, WHITE};
point c = {50, 50, 50, 50, 50, 50, WHITE};
point d = {50, -50, 50, 50, -50, 50, WHITE};

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

	/* Enable external interrupts, for when pin 6 is changed (in accordance w/ framerate). For non-flickering display. */
	EIMSK |= _BV(INT6);

	/* Start time. */
	t = 0;

	/* Start loop, with interrupts to update time & animation. */
	sei();
	while(1){}
	cli();
}

void redraw(){
	if(t<65535){
		/* Transforming. */
		rotX(&p, 1);
		rotX(&q, 1);
		rotX(&r, 1);
		rotX(&s, 1);
		rotX(&a, 1);
		rotX(&b, 1);
		rotX(&c, 1);
		rotX(&d, 1);

		rotY(&p, 1);
		rotY(&q, 1);
		rotY(&r, 1);
		rotY(&s, 1);
		rotY(&a, 1);
		rotY(&b, 1);
		rotY(&c, 1);
		rotY(&d, 1);

		rotZ(&p, 1);
		rotZ(&q, 1);
		rotZ(&r, 1);
		rotZ(&s, 1);
		rotZ(&a, 1);
		rotZ(&b, 1);
		rotZ(&c, 1);
		rotZ(&d, 1);

		/* Clearing. */
/*		clear_pt2D_p(&p);
		clear_pt2D_p(&q);
		clear_pt2D_p(&r);
		clear_pt2D_p(&s);
		clear_pt2D_p(&a);
		clear_pt2D_p(&b);
		clear_pt2D_p(&c);
		clear_pt2D_p(&d);*/
		clear_line2D_p(&p, &q);
		clear_line2D_p(&q, &r);
		clear_line2D_p(&r, &s);
		clear_line2D_p(&s, &p);
		clear_line2D_p(&a, &b);
		clear_line2D_p(&b, &c);
		clear_line2D_p(&c, &d);
		clear_line2D_p(&d, &a);
		clear_line2D_p(&a, &p);
		clear_line2D_p(&b, &q);
		clear_line2D_p(&c, &r);
		clear_line2D_p(&d, &s);

		/* Redrawing. */
/*		draw_pt2D(&p);
		draw_pt2D(&q);
		draw_pt2D(&r);
		draw_pt2D(&s);
		draw_pt2D(&a);
		draw_pt2D(&b);
		draw_pt2D(&c);
		draw_pt2D(&d);*/
		draw_line2D(&p, &q);
		draw_line2D(&q, &r);
		draw_line2D(&r, &s);
		draw_line2D(&s, &p);
		draw_line2D(&a, &b);
		draw_line2D(&b, &c);
		draw_line2D(&c, &d);
		draw_line2D(&d, &a);
		draw_line2D(&a, &p);
		draw_line2D(&b, &q);
		draw_line2D(&c, &r);
		draw_line2D(&d, &s);
	}else{t = 0;}
}

void draw_px(int16_t x, int16_t y, uint16_t col){
	int16_t fx = x + (lcdw/2);
	int16_t fy = lcdh - (y + (lcdh/2));		/* Flip y value, since maths uses y=0 at bottom but lcd uses y=0 at top. */

	if(fx >= 0 && fx <= lcdw && fy >= 0 && fy <= lcdh){
		write_cmd(PAGE_ADDRESS_SET);		/* Setting maximum & minimum y coordinate to draw. */
		write_data16(fy);
		write_data16(fy);
		write_cmd(COLUMN_ADDRESS_SET);		/* Setting maximum & minimum x coordinate to draw. */
		write_data16(fx);
		write_data16(fx);
		write_cmd(MEMORY_WRITE);			/* Setting to write memory; ie. to colour the pixel. */
		write_data16(col);
	}
}

void draw_line(int16_t x1, int16_t x2, int16_t y1, int16_t y2, uint16_t col){
/* Uses Bresenham's Line Algorithm, with an implementation adapted from:
   http://www.brackeen.com/vga/shapes.html */

	if( (x1 < (-1*(lcdw/2)) && x2 < (-1*(lcdw/2))) || (y1 < (-1*(lcdh/2)) && y2 < (-1*(lcdh/2))) || 
		(x1 > (lcdw/2) && x2 > (lcdw/2)) || (y1 > (lcdh/2) && y2 > (lcdh/2))){}else{
		
		uint16_t i, absDistX, absDistY, x, y, currX, currY;
		int16_t distX, distY, signDX, signDY;

		distX = x2 - x1;				/* x axis distance */
		distY = y2 - y1;				/* y axis distance */
		absDistX = abs(distX);			/* Absolute x axis distance */
		absDistY = abs(distY);			/* Absolute y axis distance */
		signDX = sgn(distX);			/* Sign of x axis distance (going left or right) */
		signDY = sgn(distY);			/* Sign of y axis distance (going up or down) */
		x = absDistY>>1;				/* y distance / 2 */
		y = absDistX>>1;				/* x distance / 2 */
		currX = x1;					/* Current x coordinate, to be drawn. */
		currY = y1;					/* Current y coordinate, to be drawn. */

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