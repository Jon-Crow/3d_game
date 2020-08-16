#ifndef TEXTURE_H
#define TEXTURE_H

#include "tigr.h"

#define TEXTURE_WIDTH    (64)
#define TEXTURE_HEIGHT   (64)
#define TEXTURE_COUNT    (3)
#define TEXTURE_STONE    (0)
#define TEXTURE_WOOD     (1)
#define TEXTURE_OBSIDIAN (2)

typedef struct
{
    TPixel* px[TEXTURE_WIDTH*TEXTURE_HEIGHT];
    int w, h;
} Texture;

Texture* new_texture(int w, int h);
void free_texture(Texture* tx);
void init_textures();
void free_textures();
Texture* getTexture(int t);
TPixel* getColor(Texture* tx, int x, int y);

#endif // TEXTURE_H
