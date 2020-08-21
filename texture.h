#ifndef TEXTURE_H
#define TEXTURE_H

#include "tigr.h"

#define TEXTURE_WIDTH    (64)
#define TEXTURE_HEIGHT   (64)
#define TEXTURE_COUNT    (4)
#define TEXTURE_OBSIDIAN (0)
#define TEXTURE_STONE    (1)
#define TEXTURE_WIZARD   (2)
#define TEXTURE_WOOD     (3)

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
