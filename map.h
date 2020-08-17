#ifndef MAP_H
#define MAP_H

#include "texture.h"
#include "sprite.h"

#define MAP_WIDTH    (50)
#define MAP_HEIGHT   (50)
#define SPRITE_COUNT (1)

void init_map();
void free_map();
Texture* getTextureAt(int x, int y);
int isWallAt(int x, int y);
Texture* getFloorTexture(int x, int y);
Texture* getCeilingTexture(int x, int y);
Sprite* getSprite(int i);
void sortSprites(int order[SPRITE_COUNT], float dist[SPRITE_COUNT]);

#endif // MAP_H
