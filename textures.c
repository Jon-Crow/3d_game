#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "texture.h"
#include "libbmp.h"

static Texture** textures;

TPixel* new_tpixel(int a, int r, int g, int b)
{
    TPixel* px = malloc(sizeof(TPixel));
    px->a = a;
    px->r = r;
    px->g = g;
    px->b = b;
    return px;
}
Texture* new_texture(int w, int h)
{
    int len = w*h;
    Texture* tx = malloc(sizeof(Texture));
    if(tx == NULL)
        return NULL;

    for(int i = 0; i < len; i++)
            tx->px[i] = new_tpixel(0,0,0,0);
    tx->w = w;
    tx->h = h;
    return tx;
}
void free_texture(Texture* tx)
{
    int len = tx->w * tx->h;
    for(int i = 0; i < len; i++)
        free(tx->px[i]);
    free(tx->px);
}
void init_texture(Texture* tx, const char* path)
{
    Tigr* img = tigrLoadImage(path);
    for(int x = 0; x < TEXTURE_WIDTH; x++)
    {
        for(int y = 0; y < TEXTURE_HEIGHT; y++)
        {
            TPixel* px = tx->px[y*TEXTURE_WIDTH+x];
            px->a = 255;
            px->r = img->pix[y*TEXTURE_WIDTH+x].r;
            px->g = img->pix[y*TEXTURE_WIDTH+x].g;
            px->b = img->pix[y*TEXTURE_WIDTH+x].b;
        }
    }
    tigrFree(img);
}
void init_textures()
{
    textures = malloc(TEXTURE_COUNT*sizeof(Texture));
    if(textures == NULL)
        return;
    for(int i = 0; i < TEXTURE_COUNT; i++)
        textures[i] = new_texture(TEXTURE_WIDTH, TEXTURE_HEIGHT);

    init_texture(textures[TEXTURE_STONE],    "res/textures/stone.png");
    init_texture(textures[TEXTURE_WOOD],     "res/textures/wood.png");
    init_texture(textures[TEXTURE_OBSIDIAN], "res/textures/obsidian.png");

    /*
    for(int i = 0; i < (TEXTURE_WIDTH*TEXTURE_HEIGHT); i++)
        textures[TEXTURE_STONE]->px[i]->g =i%256;
        */
}
void free_textures()
{
    for(int i = 0; i < TEXTURE_COUNT; i++)
        free_texture(textures[i]);
    free(textures);
}
Texture* getTexture(int t)
{
    if(t >= 0 && t < TEXTURE_COUNT)
        return textures[t];
    return NULL;
}
TPixel* getColor(Texture* tx, int x, int y)
{
    //printf("texture: %d\n", tx);
    int i = y*TEXTURE_WIDTH+x;
    if(i >= 0 && i < (TEXTURE_WIDTH*TEXTURE_HEIGHT))
        return tx->px[i];
    return NULL;
}









