#include <stdint.h>

typedef struct line {
	struct point *p1;
	struct point *p2;
} line;

void rotX_l(struct point *p, int16_t angle);
void rotY_l(struct point *p, int16_t angle);
void rotZ_l(struct point *p, int16_t angle);

void draw_line_l(struct line *l);
void clear_line_lp(struct line *l);
void refresh_line(struct line *l);

void draw_shape(uint8_t num, ... );
void clear_shape_p(uint8_t num, ... );
void refresh_shape(uint8_t num, ... );