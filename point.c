#include "point.h"
#include "lcd.h"
#include "cube_prog.h"

/* Rotation and projection based off maths from: http://codentronix.com/2011/04/20/simulation-of-3d-point-rotation-with-python-and-pygame/ */

void transX(struct point *p, int16_t dist){
	float nx = p->x + dist;
	p->x = nx;
}

void transY(struct point *p, int16_t dist){
	float ny = p->y + dist;
	p->y = ny;
}

void transZ(struct point *p, int16_t dist){
	float nz = p->z + dist;
	p->z = nz;
}

void rotX(struct point *p, int16_t angle) {
	float rad = angle * PI / 180;
	float cosa = cos(rad);
	float sina = sin(rad);
	float ny = p->y * cosa - p->z * sina;
	float nz = p->y * sina + p->z * cosa;
	p->y = ny;
	p->z = nz;
}

void rotY(struct point *p, int16_t angle) {
	float rad = angle * PI / 180;
	float cosa = cos(rad);
	float sina = sin(rad);
	float nx = p->x * cosa + p->z * sina;
	float nz = p->z * cosa - p->x * sina;
	p->x = nx;
	p->z = nz;
}

void rotZ(struct point *p, int16_t angle) {
	float rad = angle * PI / 180;
	float cosa = cos(rad);
	float sina = sin(rad);
	float nx = p->x * cosa - p->y * sina;
	float ny = p->x * sina + p->y * cosa;
	p->x = nx;
	p->y = ny;
}

void updX(struct point *p, float x){
	p->x = x;
}

void updY(struct point *p, float y){
	p->y = y;
}

void updZ(struct point *p, float z){
	p->z = z;
}

struct point project(struct point *p, uint16_t fov, uint16_t viewer_dist){
	float factor = fov / (viewer_dist + p->z);
	float nx = p->x * factor + display.width / 2;
	float ny = -1 * p->y * factor + display.height / 2;
	point proj = {nx, ny, 1, p->col};
	return proj;
}

void draw_pt2D(struct point *p){
	draw_px((int16_t) p->x, (int16_t) p->y, p->col);
}

void clear_pt2D(struct point *p){
	draw_px((int16_t) p->x, (int16_t) p->y, display.background);
}

void draw_line2D(struct point *p1, struct point *p2){
	draw_line(p1->x, p2->x, p1->y, p2->y, p1->col);
}

void clear_line2D(struct point *p1, struct point *p2){
	draw_line(p1->x, p2->x, p1->y, p2->y, display.background);
}