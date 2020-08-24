#ifndef TEXTURE_H
#define TEXTURE_H

#include "tigr.h"

#define TEXTURE_WIDTH                (32)
#define TEXTURE_HEIGHT               (32)
#define TEXTURE_COUNT (14)
#define TEXTURE_BIRCH_PLANKS (0)
#define TEXTURE_COBBLESTONE (1)
#define TEXTURE_CRACKED_STONE_BRICKS (2)
#define TEXTURE_DARK_OAK_PLANKS (3)
#define TEXTURE_DIRT (4)
#define TEXTURE_END_STONE_BRICKS (5)
#define TEXTURE_GRASS_BLOCK_TOP (6)
#define TEXTURE_GRASS_PATH_TOP (7)
#define TEXTURE_MOSSY_STONE_BRICKS (8)
#define TEXTURE_OAK_PLANKS (9)
#define TEXTURE_QUARTZ_BRICKS (10)
#define TEXTURE_QUARTZ_PILLAR (11)
#define TEXTURE_SPRUCE_PLANKS (12)
#define TEXTURE_STONE_BRICKS (13)


typedef struct
{
    TPixel* px[TEXTURE_WIDTH*TEXTURE_HEIGHT];
    int w, h;
} Texture;

Texture* new_texture(int w, int h);
void free_texture(Texture* tx);
void init_texture(Texture* tx, const char* path);
void init_textures();
void free_textures();
Texture* getTexture(int t);
TPixel* getColor(Texture* tx, int x, int y);

#endif // TEXTURE_H
