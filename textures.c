#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "texture.h"
#include "animation.h"

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
    if(img == NULL)
    {
        printf("Could not load %s\n", path);
        return;
    }
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

	init_texture(textures[TEXTURE_BARREL], "res/textures/barrel.png");
	init_texture(textures[TEXTURE_BIRCH_PLANKS], "res/textures/birch_planks.png");
	init_texture(textures[TEXTURE_COBBLESTONE], "res/textures/cobblestone.png");
	init_texture(textures[TEXTURE_CRACKED_STONE_BRICKS], "res/textures/cracked_stone_bricks.png");
	init_texture(textures[TEXTURE_DARK_OAK_PLANKS], "res/textures/dark_oak_planks.png");
	init_texture(textures[TEXTURE_DIRT], "res/textures/dirt.png");
	init_texture(textures[TEXTURE_END_STONE_BRICKS], "res/textures/end_stone_bricks.png");
	init_texture(textures[TEXTURE_GRASS_BLOCK_TOP], "res/textures/grass_block_top.png");
	init_texture(textures[TEXTURE_GRASS_PATH_TOP], "res/textures/grass_path_top.png");
	init_texture(textures[TEXTURE_MOSSY_STONE_BRICKS], "res/textures/mossy_stone_bricks.png");
	init_texture(textures[TEXTURE_OAK_PLANKS], "res/textures/oak_planks.png");
	init_texture(textures[TEXTURE_PILLAR], "res/textures/pillar.png");
	init_texture(textures[TEXTURE_QUARTZ_BRICKS], "res/textures/quartz_bricks.png");
	init_texture(textures[TEXTURE_QUARTZ_PILLAR], "res/textures/quartz_pillar.png");
	init_texture(textures[TEXTURE_SPRUCE_PLANKS], "res/textures/spruce_planks.png");
	init_texture(textures[TEXTURE_STONE_BRICKS], "res/textures/stone_bricks.png");

	init_animationTextures();
}
void free_textures()
{
    for(int i = 0; i < TEXTURE_COUNT; i++)
        free_texture(textures[i]);
    free(textures);
    free_animationTextures();
}
Texture* getTexture(int t)
{
    if(t >= 0 && t < TEXTURE_COUNT)
        return textures[t];
    return NULL;
}
TPixel* getColor(Texture* tx, int x, int y)
{
    int i = y*TEXTURE_WIDTH+x;
    if(i >= 0 && i < (TEXTURE_WIDTH*TEXTURE_HEIGHT))
        return tx->px[i];
    return NULL;
}









