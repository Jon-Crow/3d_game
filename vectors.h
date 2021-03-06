#ifndef VECTORS_H
#define VECTORS_H

typedef struct
{
    float x, y;
} Vector2f;

Vector2f* new_vector2f(float x, float y);
void free_vector2f(Vector2f* v);
float magnitude(Vector2f* v);
float direction(Vector2f* v);
float directionTo(Vector2f* p1, Vector2f* p2);
void normalize(Vector2f* v);
void pointTo(Vector2f* v, Vector2f* p1, Vector2f* p2);
void rotateVector2f(Vector2f* v, float rad);

#endif // VECTORS_H
