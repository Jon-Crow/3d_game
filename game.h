#ifndef GAME_H
#define GAME_H

#include "tigr.h"
#include "vectors.h"

#define SCREEN_WIDTH  (800)
#define SCREEN_HEIGHT (600)

typedef struct
{
    Vector2f* pos;
    Vector2f* dir;
    Vector2f* plane;
} Player;

void init_game();
void free_game();
void update(Tigr* screen, float delta);
void render(Tigr* screen);

#endif // GAME_H
