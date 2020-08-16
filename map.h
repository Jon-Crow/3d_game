#ifndef MAP_H
#define MAP_H

#include "texture.h"

void init_map();
void free_map();
Texture* getTextureAt(int x, int y);
int isWallAt(int x, int y);
Texture* getFloorTexture();
Texture* getCeilingTexture();

#endif // MAP_H
