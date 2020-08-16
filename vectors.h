#ifndef VECTORS_H
#define VECTORS_H

typedef struct
{
    float x, y;
} Vector2f;

Vector2f* new_vector2f(float x, float y);
void free_vector2f(Vector2f* v);

#endif // VECTORS_H
