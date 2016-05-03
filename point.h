#include <stdint.h>
#include <math.h>
#define PI 3.14159265

typedef struct point {
	float x, y, z;
	float xp, yp, zp;
	uint16_t col;
} point;

void transX(struct point *p, float dist);
void transY(struct point *p, float dist);
void transZ(struct point *p, float dist);

void rotX(struct point *p, int16_t angle);
void rotY(struct point *p, int16_t angle);
void rotZ(struct point *p, int16_t angle);

void updX(struct point *p, float x);
void updY(struct point *p, float y);
void updZ(struct point *p, float z);

struct point project(struct point *p, uint16_t fov, uint16_t viewer_dist);

void draw_pt(struct point *p);
void clear_pt(struct point *p);
void refresh_pt(struct point *p);

void draw_line_pt(struct point *p1, struct point *p2);
void clear_line_pt(struct point *p1, struct point *p2);

void clear_pt_p(struct point *p);
void clear_line_pt_p(struct point *p1, struct point *p2);