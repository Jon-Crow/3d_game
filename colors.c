#include <stdlib.h>
#include <stddef.h>

#include "colors.h"

static TPixel* clrs[COLOR_COUNT];

TPixel* new_color(int r, int g, int b)
{
    TPixel* clr = malloc(sizeof(TPixel));
    if(clr == NULL)
        return NULL;
    clr->r = r;
    clr->g = g;
    clr->b = b;
    clr->a = 255;
    return clr;
}
void init_colors()
{
    clrs[COLOR_BLACK] = new_color(0,0,0);
    clrs[COLOR_WHITE] = new_color(255,255,255);
    clrs[COLOR_RED]   = new_color(255,0,0);
    clrs[COLOR_GREEN] = new_color(0,255,0);
    clrs[COLOR_BLUE]  = new_color(0,0,255);
}
void free_colors()
{
    for(int i = 0; i < COLOR_COUNT; i++)
        free(clrs[i]);
}
TPixel* color(int clr)
{
    if(clr >= 0 && clr < COLOR_COUNT)
        return clrs[clr];
    return NULL;
}
