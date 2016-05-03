#include "line.h"
#include "point.h"
#include "laforcuba.h"
#include "lcd.h"
#include <stdarg.h>

void rotX_l(struct point *p, int16_t angle){

}

void rotY_l(struct point *p, int16_t angle){

}

void rotZ_l(struct point *p, int16_t angle){
	
}

void draw_line_l(struct line *l){
	draw_line(l->p1->x, l->p2->x, l->p1->y, l->p2->y, l->p1->col);
	l->p1->xp = l->p1->x;
	l->p1->yp = l->p1->y;
	l->p1->zp = l->p1->z;
	l->p2->xp = l->p2->x;
	l->p2->yp = l->p2->y;
	l->p2->zp = l->p2->z;
}

void clear_line_lp(struct line *l){
	draw_line(l->p1->xp, l->p2->xp, l->p1->yp, l->p2->yp, display.background);
}

void refresh_line(struct line *l){
	draw_line(l->p1->xp, l->p2->xp, l->p1->yp, l->p2->yp, display.background);
	draw_line(l->p1->x, l->p2->x, l->p1->y, l->p2->y, l->p1->col);
	l->p1->xp = l->p1->x;
	l->p1->yp = l->p1->y;
	l->p1->zp = l->p1->z;
	l->p2->xp = l->p2->x;
	l->p2->yp = l->p2->y;
	l->p2->zp = l->p2->z;
}

void draw_shape(uint8_t num, ... ){
	uint8_t i;
	line l;

	va_list al;
	va_start(al, num);

	for(i=0;i<num;i++){
		l = va_arg(al, line);
		draw_line_l(&l);
	}

	va_end(al);
}

void clear_shape_p(uint8_t num, ... ){
	uint8_t i;
	line l;

	va_list al;
	va_start(al, num);

	for(i=0;i<num;i++){
		l = va_arg(al, line);
		clear_line_lp(&l);
	}

	va_end(al);
}

void refresh_shape(uint8_t num, ... ){
/* NOTE: DOESN'T ACTUALLY WORK IF USING display.background TO CLEAR FOR SOME REASON */
	uint8_t i;
	line *l;
	point *ps[num+1];

	va_list al;
	va_start(al, num);

	for(i=0;i<num;i++){
		l = va_arg(al, line*);
		draw_line(l->p1->xp, l->p2->xp, l->p1->yp, l->p2->yp, BLACK);
		draw_line(l->p1->x, l->p2->x, l->p1->y, l->p2->y, l->p1->col);
		ps[i] = l->p1;
	}

	ps[num+1] = l->p2;

	for(i=0;i<=num;i++){
		ps[i]->xp = ps[i]->x;
		ps[i]->yp = ps[i]->y;
		ps[i]->zp = ps[i]->z;
	}

	va_end(al);
}