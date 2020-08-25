#ifndef GAME_H
#define GAME_H

#include "tigr.h"
#include "vectors.h"
#include "sprite.h"
#include "statblock.h"

typedef struct
{
    Vector2f* pos;
    Vector2f* dir;
    Vector2f* plane;
    StatBlock* stats;
} Player;

void init_game();
void free_game();
void updateGame(Tigr* screen, float delta);
void renderGame(Tigr* screen);

void actor_decoration(Sprite* sp, int id, float delta);
void actor_enemy(Sprite* sp, int id, float delta);
void freeType_decoration(void* type);
void freeType_enemy(void* type);

void attack_bandit(Enemy* bandit, StatBlock* tar);

#endif // GAME_H
