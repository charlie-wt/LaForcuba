#include "cube_prog.h"
#include "lcd.h"
#include "ili934x.h"
#include "point.h"
#include <avr/interrupt.h>
#include <stdlib.h>

uint16_t t;		/* Time. */
point p = {160, 120, 1, BLUE};
/*line2D l = {100, 200, 100, 200, YELLOW};
point_mov pm = {30, 30, 1, 0, GREEN};*/

void main(void) {
	/* 8MHz clock, no prescaling. */
	CLKPR = (1 << CLKPCE);
	CLKPR = 0;

	/* Initialise the LCD display driver */
	init_lcd();
	set_frame_rate_hz(61);

	/* Enable external interrupts, for when pin 6 is changed. For non-flickering display. */
	EIMSK |= _BV(INT6);

	t = 0;

	/* Start animation loop, with interrupts to update time. */
	sei();
	while(1){
/*		redraw();*/
	}
	cli();
}

/*void animate_pt(point_mov *p){
	draw_px(p->x, p->y, display.background);
	p->x += p->movx;
	p->y += p->movy;
}*/

void redraw(){
	if(t<display.width){
/*		draw_line(49+t, 74+t, 50, 74+t, display.background);
		draw_line(50+t, 75+t, 50, 75+t, CYAN);
		draw_px(34+t, 35, display.background);
		draw_px(35+t, 35, LIME_GREEN);*/
		
		transXdraw(&p, 1);
		transYdraw(&p, 1);

/*		draw_pt2D(&p);*/
/*		draw_pointmov(pm);
		draw_point(p);
		draw_line2D(l);*/
	}else{t = 0;}
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
/* Uses Bresenham's Line Algorithm, with an implementation adapted from:
   http://www.brackeen.com/vga/shapes.html */
	uint16_t i, absDistX, absDistY, x, y, currX, currY;
	int distX, distY, signDX, signDY;

	if((x1 > display.width && x2 > display.width) || (y1 > display.height && y2 > display.height)){}else{
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

/*void draw_point(point p){
	draw_px(p.x, p.y, p.col);
}

void draw_pointmov(point_mov p){
	draw_px(p.x, p.y, p.col);
}

void draw_line2D(line2D l){
	draw_line(l.x1, l.x2, l.y1, l.y2, l.col);
}

void draw_line3D(line3D l){
	
}*/

ISR( INT6_vect ){
	t++;
	redraw();
/*	clear_pt2D(&p);*/
/*	transXdraw(&p, 1);
	transYdraw(&p, 1);*/
/*	animate_pt(&pm);*/
}