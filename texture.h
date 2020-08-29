#ifndef TEXTURE_H
#define TEXTURE_H

#include "tigr.h"

#define TEXTURE_WIDTH                (32)
#define TEXTURE_HEIGHT               (32)
#define TEXTURE_COUNT (17)
#define TEXTURE_BARREL (0)
#define TEXTURE_BIRCH_PLANKS (1)
#define TEXTURE_COBBLESTONE (2)
#define TEXTURE_CRACKED_STONE_BRICKS (3)
#define TEXTURE_DARK_OAK_PLANKS (4)
#define TEXTURE_DIRT (5)
#define TEXTURE_END_STONE_BRICKS (6)
#define TEXTURE_GRASS_BLOCK_TOP (7)
#define TEXTURE_GRASS_PATH_TOP (8)
#define TEXTURE_MOSSY_STONE_BRICKS (9)
#define TEXTURE_OAK_PLANKS (10)
#define TEXTURE_PILLAR (11)
#define TEXTURE_QUARTZ_BRICKS (12)
#define TEXTURE_QUARTZ_PILLAR (13)
#define TEXTURE_SPRUCE_PLANKS (14)
#define TEXTURE_STONE_BRICKS (15)
#define TEXTURE_FIREBALL (16)


typedef struct
{
    TPixel* px[TEXTURE_WIDTH*TEXTURE_HEIGHT];
    int w, h;
} Texture;

Tigr* scaleImage(Tigr* img, int w, int h);
Texture* new_texture(int w, int h);
void free_texture(Texture* tx);
void init_texture(Texture* tx, const char* path);
void init_textures();
void free_textures();
Texture* getTexture(int t);
TPixel* getColor(Texture* tx, int x, int y);

#endif // TEXTURE_H
