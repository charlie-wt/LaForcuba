#include "point.h"
#include "lcd.h"
#include "cube_prog.h"

/* Rotation and projection based off maths from: http://codentronix.com/2011/04/20/simulation-of-3d-point-rotation-with-python-and-pygame/ */

void transX(struct point *p, int16_t dist){
	int16_t x = p->x + dist;
	p->x = x;
}

void transY(struct point *p, int16_t dist){
	int16_t y = p->y + dist;
	p->y = y;
}

void transZ(struct point *p, int16_t dist){
	int16_t z = p->z + dist;
	p->z = z;
}

void rotX(struct point *p, int16_t angle) {
	float rad = angle * PI / 180;
	double cosa = cos(rad);
	double sina = sin(rad);
	int16_t y = p->y * cosa - p->z * sina;
	int16_t z = p->y * sina + p->z * cosa;
	p->y = y;
	p->z = z;
}

void rotY(struct point *p, int16_t angle) {
	float rad = angle * PI / 180;
	double cosa = cos(rad);
	double sina = sin(rad);
	int16_t z = p->z * cosa - p->x * sina;
	int16_t x = p->z * sina + p->x * cosa;
	p->x = x;
	p->z = z;
}

void rotZ(struct point *p, int16_t angle) {
	float rad = angle * PI / 180;
	double cosa = cos(rad);
	double sina = sin(rad);
	int16_t x = p->x * cosa - p->y * sina;
	int16_t y = p->x * sina + p->y * cosa;
	p->x = x;
	p->y = y;
}

void updX(struct point *p, int16_t x){
	p->x = x;
}

void updY(struct point *p, int16_t y){
	p->y = y;
}

void updZ(struct point *p, int16_t z){
	p->z = z;
}

struct point project(struct point *p, uint16_t fov, uint16_t viewer_dist){
	float factor = fov / (viewer_dist + p->z);
	int16_t x = p->x * factor + display.width / 2;
	int16_t y = -1 * p->y * factor + display.height / 2;
	point proj = {x, y, 1, p->col};
	return proj;
}

void draw_pt2D(struct point *p){
	draw_px(p->x, p->y, p->col);
}

void clear_pt2D(struct point *p){
	draw_px(p->x, p->y, display.background);
}