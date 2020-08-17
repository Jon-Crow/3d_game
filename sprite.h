#ifndef SPRITE_H
#define SPRITE_H

#include "vectors.h"

#define SPRITE_TYPE_DECORATION (0)
#define SPRITE_TYPE_ENEMY      (1)
#define ENEMY_VISION_DIST      (10.0f)
#define ENEMY_MIN_DIST         (0.25f)
#define ENEMY_SPEED            (1.5f)

typedef struct
{
    Vector2f* pos;
    Vector2f* dir;
    int tx;
    int type;
} Sprite;

Sprite* new_sprite(float x, float y, int tx, int type);
void free_sprite(Sprite* sp);

#endif // SPRITE_H
