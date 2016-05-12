#include <stdint.h>
#include <math.h>
#define PI 3.14159265

typedef struct point {
	float x, y, z;
	float xp, yp, zp;
	uint16_t col;
} point;

/* Translation */
void transX(struct point *p, float dist);
void transY(struct point *p, float dist);
void transZ(struct point *p, float dist);

/* Rotation */
void rotX(struct point *p, int16_t angle);
void rotY(struct point *p, int16_t angle);
void rotZ(struct point *p, int16_t angle);

/* Update coordinates with new ones */
void updX(struct point *p, float x);
void updY(struct point *p, float y);
void updZ(struct point *p, float z);

/* Project 3D coordinates onto 2D */
struct point project(struct point *p, uint16_t fov, uint16_t viewer_dist);

/* Drawing methods for points, taking a point struct. */
void draw_pt(struct point *p);
void clear_pt(struct point *p);
void refresh_pt(struct point *p);		/* Clears the previous point and draws the new one. */

/* For drawing lines with point structs. */
void draw_line_pt(struct point *p1, struct point *p2);
void clear_line_pt(struct point *p1, struct point *p2);

/* For clearing the previous location of a point/line. */
void clear_pt_p(struct point *p);
void clear_line_pt_p(struct point *p1, struct point *p2);