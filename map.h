#ifndef MAP_H
#define MAP_H

#include "texture.h"
#include "sprite.h"
#include "game.h"

#define MAP_WIDTH    (50)
#define MAP_HEIGHT   (50)
#define SPRITE_MAX   (256)

void init_map();
void free_map();
Texture* getTextureAt(int x, int y);
int isWallAt(int x, int y);
Texture* getFloorTexture(int x, int y);
Texture* getCeilingTexture(int x, int y);
Sprite* getSprite(int i);
void sortSprites(int order[SPRITE_MAX], float dist[SPRITE_MAX]);
int getSpriteCount();
Sprite* addSprite(float x, float y, int tx, void (*actor)(Sprite*, int, float), void (*freeType)(void*), void* type);
void removeSprite(Sprite* sp);
void removeSpriteAt(int sprite);

void loadMap(Player* plyr, int m);

#endif // MAP_H
