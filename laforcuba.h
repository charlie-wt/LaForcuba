#include <stdint.h>

#define sgn(x) ((x<0)?-1:((x>0)?1:0))

void redraw();																		/* Called on screen refresh; for updating and redrawing code. */
void draw_px(int16_t x, int16_t y, uint16_t col);									/* Draw a single pixel from coordinates */
void draw_line(int16_t x1, int16_t x2, int16_t y1, int16_t y2, uint16_t col);		/* Draw a line from coordinates */