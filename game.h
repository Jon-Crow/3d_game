#ifndef GAME_H
#define GAME_H

#include "tigr.h"

void init_game();
void free_game();
void update(Tigr* screen, float delta);
void render(Tigr* screen);

#endif // GAME_H
