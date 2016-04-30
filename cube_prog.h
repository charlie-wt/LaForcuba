#include <stdint.h>

#define sgn(x) ((x<0)?-1:((x>0)?1:0))

void redraw();
void draw_px(uint16_t x, uint16_t y, uint16_t col);
void draw_line(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t col);