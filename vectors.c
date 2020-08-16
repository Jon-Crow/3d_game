#include <stddef.h>
#include <stdlib.h>

#include "vectors.h"

Vector2f* new_vector2f(float x, float y)
{
    Vector2f* v = malloc(sizeof(Vector2f));
    if(v == NULL)
        return NULL;
    v->x = x;
    v->y = y;
    return v;
}
void free_vector2f(Vector2f* v)
{
    free(v);
}
