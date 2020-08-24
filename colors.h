#ifndef COLORS_H
#define COLORS_H

#include "tigr.h"

#define COLOR_COUNT (5)
#define COLOR_BLACK (0)
#define COLOR_WHITE (1)
#define COLOR_RED   (2)
#define COLOR_GREEN (3)
#define COLOR_BLUE  (4)

void init_colors();
void free_colors();
TPixel* color(int clr);

#endif // COLORS_H
