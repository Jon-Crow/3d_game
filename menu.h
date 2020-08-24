#ifndef MENU_H
#define MENU_H

#include "tigr.h"

void init_menu();
void free_menu();
void updateMenu(Tigr* screen, float delta);
void renderMenu(Tigr* screen);

#endif // MENU_H
