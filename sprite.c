#include <stddef.h>
#include <stdlib.h>

#include "sprite.h"

Sprite* new_sprite(float x, float y, int tx, int type)
{
    Sprite* sp = malloc(sizeof(Sprite));
    if(sp == NULL)
        return NULL;
    sp->pos = new_vector2f(x, y);
    sp->dir = new_vector2f(1, 0);
    sp->tx = tx;
    sp->type = type;
    return sp;
}
void free_sprite(Sprite* sp)
{
    free_vector2f(sp->pos);
    free(sp);
}





