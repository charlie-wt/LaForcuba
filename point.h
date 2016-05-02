#include <stdint.h>
#include <math.h>
#define PI 3.14159265

typedef struct point {
	float x, y, z;
	uint16_t col;
} point;

void transX(struct point *p, int16_t dist);
void transY(struct point *p, int16_t dist);
void transZ(struct point *p, int16_t dist);
void rotX(struct point *p, int16_t angle);
void rotY(struct point *p, int16_t angle);
void rotZ(struct point *p, int16_t angle);
void updX(struct point *p, float x);
void updY(struct point *p, float y);
void updZ(struct point *p, float z);
struct point project(struct point *p, uint16_t fov, uint16_t viewer_dist);
void draw_pt2D(struct point *p);
void clear_pt2D(struct point *p);
void draw_line2D(struct point *p1, struct point *p2);
void clear_line2D(struct point *p1, struct point *p2);