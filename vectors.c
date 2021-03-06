#include <math.h>
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
float magnitude(Vector2f* v)
{
    return sqrt(v->x*v->x + v->y*v->y);
}
float direction(Vector2f* v)
{
    return (float)atan2(v->y, v->x);
}
float directionTo(Vector2f* p1, Vector2f* p2)
{
    return (float)atan2(p2->y - p1->y, p2->x - p1->x);
}
void normalize(Vector2f* v)
{
    float mag = magnitude(v);
    v->x /= mag;
    v->y /= mag;
}
void pointTo(Vector2f* v, Vector2f* p1, Vector2f* p2)
{
    v->x = p2->x - p1->x;
    v->y = p2->y - p1->y;
    normalize(v);
}
void rotateVector2f(Vector2f* v, float rad)
{
    float oldX, oldY, cosRad, sinRad;
    oldX = v->x;
    oldY = v->y;
    cosRad = cos(rad);
    sinRad = sin(rad);
    v->x = v->x*cosRad - v->y*sinRad;
    v->y = oldX*sinRad + oldY*cosRad;
}








