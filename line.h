#include <stdint.h>

typedef struct line {
	struct point *p1;
	struct point *p2;
} line;

/* Drawing methods for lines, taking a line struct. */
void draw_line_l(struct line *l);
void clear_line_lp(struct line *l);
void refresh_line(struct line *l);		/* Clears the previous line and draws the new one. */

/* Drawing methods for shapes, taking an undefined amount of lines to build them up. */
void draw_shape(uint8_t num, ... );
void clear_shape_p(uint8_t num, ... );
void refresh_shape(uint8_t num, ... );