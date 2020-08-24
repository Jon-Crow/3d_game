#include "gamestate.h"

static void (*updateFunc)(Tigr*, float);
static void (*renderFunc)(Tigr*);

void setGameState(void (*update)(Tigr*, float), void (*render)(Tigr*))
{
    updateFunc = update;
    renderFunc = render;
}
void update(Tigr* screen, float delta)
{
    updateFunc(screen, delta);
}
void render(Tigr* screen)
{
    renderFunc(screen);
}
