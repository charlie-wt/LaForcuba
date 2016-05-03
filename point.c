#include "point.h"
#include "lcd.h"
#include "laforcuba.h"

/* Rotation and projection based off implementations from: http://codentronix.com/2011/04/20/simulation-of-3d-point-rotation-with-python-and-pygame/ */

void transX(struct point *p, float dist){
	float nx = p->x + dist;
	p->x = nx;
}

void transY(struct point *p, float dist){
	float ny = p->y + dist;
	p->y = ny;
}

void transZ(struct point *p, float dist){
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

/* AS YET UNTESTED */
struct point project(struct point *p, uint16_t fov, uint16_t viewer_dist){
	float factor = fov / (viewer_dist + p->z);
	float nx = p->x * factor + display.width / 2;
	float ny = -1 * p->y * factor + display.height / 2;
	point proj = {nx, ny, 1, p->xp, p->yp, p->zp, p->col};
	return proj;
}

void draw_pt(struct point *p){
	draw_px((int16_t) p->x, (int16_t) p->y, p->col);
	p->xp = p->x;
	p->yp = p->y;
	p->zp = p->z;
}

void clear_pt(struct point *p){
	draw_px((int16_t) p->x, (int16_t) p->y, display.background);
}

void refresh_pt(struct point *p){
	clear_pt(p);
	draw_pt(p);
}

void draw_line_pt(struct point *p1, struct point *p2){
	draw_line(p1->x, p2->x, p1->y, p2->y, p1->col);
	p1->xp = p1->x;
	p1->yp = p1->y;
	p1->zp = p1->z;
	p2->xp = p2->x;
	p2->yp = p2->y;
	p2->zp = p2->z;
}

void clear_line_pt(struct point *p1, struct point *p2){
	draw_line(p1->x, p2->x, p1->y, p2->y, display.background);
}

void clear_pt_p(struct point *p){
	draw_px(p->xp, p->yp, display.background);
}

void clear_line_pt_p(struct point *p1, struct point *p2){
	draw_line(p1->xp, p2->xp, p1->yp, p2->yp, display.background);
}