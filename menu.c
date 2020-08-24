#include "menu.h"
#include "colors.h"
#include "game.h"
#include "gamestate.h"

void init_menu()
{

}
void free_menu()
{

}
void updateMenu(Tigr* screen, float delta)
{
    if(tigrKeyDown(screen, 'E'))
        setGameState(updateGame, renderGame);
}
void renderMenu(Tigr* screen)
{
    tigrFill(screen, 0, 0, screen->w, screen->h, *color(COLOR_BLACK));
}
