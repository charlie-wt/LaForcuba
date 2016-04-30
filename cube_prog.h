#include <stdint.h>

#define sgn(x) ((x<0)?-1:((x>0)?1:0))

/*typedef struct {
	uint16_t x, y, col;
} point;*/

/*typedef struct {
	uint16_t x1, x2;
	uint16_t y1, y2;
	uint16_t col;
} line2D;

typedef struct {
	uint16_t x1, x2;
	uint16_t y1, y2;
	uint16_t z1, z2;
	uint16_t col;
} line3D;*/

/*typedef struct {
	uint16_t x, y;
	uint16_t movx, movy;
	uint16_t col;
} point_mov;*/

/*void animate_pt(point_mov *p);*/
void redraw();
void draw_px(uint16_t x, uint16_t y, uint16_t col);
void draw_line(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t col);
/*void draw_point(point p);
void draw_pointmov(point_mov p);
void draw_line2D(line2D l);
void draw_line3D(line3D l);*/