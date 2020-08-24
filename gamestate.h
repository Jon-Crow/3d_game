#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "tigr.h"

void setGameState(void (*update)(Tigr*, float), void (*render)(Tigr*));
void update(Tigr* screen, float delta);
void render(Tigr* screen);

#endif // GAMESTATE_H
