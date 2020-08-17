#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "vectors.h"
#include "texture.h"
#include "map.h"

#define POS_X   (plyr->pos->x)
#define POS_Y   (plyr->pos->y)
#define DIR_X   (plyr->dir->x)
#define DIR_Y   (plyr->dir->y)
#define PLANE_X (plyr->plane->x)
#define PLANE_Y (plyr->plane->y)
#define RENDER_DIVISION (2)

typedef struct
{
    Vector2f* pos;
    Vector2f* dir;
    Vector2f* plane;
} Player;

static Player* plyr;
static int odd;
static int spriteOrder[SPRITE_COUNT];
static float spriteDist[SPRITE_COUNT];
static float zBuff[SCREEN_WIDTH];

Player* new_player()
{
    Player* plyr = malloc(sizeof(Player));
    if(plyr == NULL)
        return NULL;

    plyr->pos   = new_vector2f(1.5f,1.5f);
    plyr->dir   = new_vector2f(1.0f,0.0f);
    plyr->plane = new_vector2f(0.0f,0.66f);
    return plyr;
}
void free_player(Player* plyr)
{
    free_vector2f(plyr->dir);
    free_vector2f(plyr->plane);
    free(plyr);
}
void init_game()
{
    plyr = new_player();
    odd = 0;
    for(int i = 0; i < SPRITE_COUNT; i++)
    {
        spriteOrder[i] = 0;
        spriteDist[i] = 0;
    }
    for(int i = 0; i < SCREEN_WIDTH; i++)
        zBuff[i] = 0;
}
void free_game()
{
    free_player(plyr);
}
void setPixelRGB(Tigr* screen, int x, int y, int r, int g, int b)
{
    TPixel* px = &(screen->pix[y*screen->w+x]);
    px->r = r;
    px->g = g;
    px->b = b;
}
void setPixel(Tigr* screen, int x, int y, TPixel* clr)
{
    if( (x >= 0 && x < screen->w) && (y >= 0 && y < screen->h) )
    {
        TPixel* px = &(screen->pix[y*screen->w+x]);
        if(px == NULL)
            return;
        px->r = clr->r;
        px->g = clr->g;
        px->b = clr->b;
    }
}
void setPixelScaled(Tigr* screen, int x, int y, TPixel* clr, float scale)
{
    if( (x >= 0 && x < screen->w) && (y >= 0 && y < screen->h) )
    {
        TPixel* px = &(screen->pix[y*screen->w+x]);
        if(px == NULL)
            return;
        px->r = (int)(clr->r*scale);
        px->g = (int)(clr->g*scale);
        px->b = (int)(clr->b*scale);
    }
}
void move(Vector2f* pos, Vector2f* dir, float spd)
{
    float oldX = pos->x,
          oldY = pos->y;
    pos->x += dir->x*spd;
    if(isWallAt((int)pos->x, (int)pos->y))
        pos->x = oldX;
    pos->y += dir->y*spd;
    if(isWallAt((int)pos->x, (int)pos->y))
        pos->y = oldY;
}
void rotate(float spd)
{
    float oldDirX = DIR_X,
          oldPlaneX = PLANE_X;
    DIR_X = (float)(DIR_X * cos(-spd) - DIR_Y * sin(-spd));
    DIR_Y = (float)(oldDirX * sin(-spd) + DIR_Y * cos(-spd));
    PLANE_X = (float)(PLANE_X * cos(-spd) - PLANE_Y * sin(-spd));
    PLANE_Y = (float)(oldPlaneX * sin(-spd) + PLANE_Y * cos(-spd));
}
void updateSprites(float delta)
{
    Sprite* sp;
    for(int i = 0; i < SPRITE_COUNT; i++)
    {
        sp = getSprite(i);
        spriteOrder[i] = i;
        spriteDist[i] = ((POS_X - sp->pos->x) * (POS_X - sp->pos->x) + (POS_Y - sp->pos->y) * (POS_Y - sp->pos->y));
        if(sp->type == SPRITE_TYPE_ENEMY)
        {
            if(spriteDist[i] < ENEMY_VISION_DIST && spriteDist[i] > ENEMY_MIN_DIST)
            {
                pointTo(sp->dir, sp->pos, plyr->pos);
                move(sp->pos, sp->dir, delta*ENEMY_SPEED);
            }
        }
    }
    sortSprites(spriteOrder, spriteDist);
}
void update(Tigr* screen, float delta)
{
    updateSprites(delta);
    if(tigrKeyHeld(screen, 'W'))
        move(plyr->pos, plyr->dir, delta*2);
    if(tigrKeyHeld(screen, 'S'))
        move(plyr->pos, plyr->dir, -delta*2);
    if(tigrKeyHeld(screen, 'A'))
        rotate(delta*2);
    if(tigrKeyHeld(screen, 'D'))
        rotate(-delta*2);
}
void renderWalls(Tigr* screen, int w, int h)
{
    for(int x = odd; x < w; x+=RENDER_DIVISION)
    {
        //calculate ray position and direction
        float camX = 2.0f * x / w - 1; //x-coordinate in camera space
        float rayDirX = DIR_X + PLANE_X * camX;
        float rayDirY = DIR_Y + PLANE_Y * camX;

        //which box of the map we're in
        int mapX = (int)floor(POS_X);
        int mapY = (int)floor(POS_Y);

        //length of ray from current position to next x or y-side
        float sideDistX;
        float sideDistY;

         //length of ray from one x or y-side to next x or y-side
        float deltaDistX = fabs(1.0f/rayDirX);
        float deltaDistY = fabs(1.0f/rayDirY);

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;
        //calculate step and initial sideDist
        if(rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (POS_X - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - POS_X) * deltaDistX;
        }
        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (POS_Y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - POS_Y) * deltaDistY;
        }

        int side,
            hit = 0;
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (isWallAt(mapX, mapY))
                hit = 1;
        }

        float perpWallDist;
        //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0)
            perpWallDist = (mapX - POS_X + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - POS_Y + (1 - stepY) / 2) / rayDirY;

        //Calculate height of line to draw on screen
        int lineHeight = (int)(h / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + h / 2;
        if(drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if(drawEnd >= h)
            drawEnd = h - 1;

        //calculate value of wallX
        float wallX; //where exactly the wall was hit
        if(side == 1)
            wallX = POS_X + perpWallDist * rayDirX;
        else
            wallX = POS_Y + perpWallDist * rayDirY;
        wallX -= (int)wallX;

        //x coordinate on the texture
        int texX = (int)(wallX * TEXTURE_WIDTH);
        if(side == 0 && rayDirX > 0)
            texX = TEXTURE_WIDTH - texX - 1;
        if(side == 1 && rayDirY < 0)
            texX = TEXTURE_WIDTH - texX - 1;

        // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
        // How much to increase the texture coordinate per screen pixel
        float step = 1.0 * TEXTURE_HEIGHT / lineHeight;
        // Starting texture coordinate
        float texPos = (drawStart - h / 2 + lineHeight / 2) * step;

        for(int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (TEXTURE_HEIGHT - 1);
            texPos += step;
            TPixel* px = getColor(getTextureAt(mapX, mapY), texX, texY);

            //FOR FOG
            //setPixelScaled(screen, x, y, px, fmin(1.0f, 2.0f/perpWallDist));
            if(side == 0)
                setPixel(screen, x, y, px);
            else
                setPixelScaled(screen, x, y, px, 0.67f);
        }

        zBuff[x] = perpWallDist;
    }
}
void renderFloorCeiling(Tigr* screen, int w, int h)
{
    for(int y = 0; y < h; y++)
    {
        // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
        float rayDirX0 = DIR_X - PLANE_X;
        float rayDirY0 = DIR_Y - PLANE_Y;
        float rayDirX1 = DIR_X + PLANE_X;
        float rayDirY1 = DIR_Y + PLANE_Y;

        // Current y position compared to the center of the screen (the horizon)
        int p = y - h/2;

        // Vertical position of the camera.
        float posZ = h/2.0f;

        // Horizontal distance from the camera to the floor for the current row.
        // 0.5 is the z position exactly in the middle between floor and ceiling.
        float rowDistance = posZ/p;

        // calculate the real world step vector we have to add for each x (parallel to camera plane)
        // adding step by step avoids multiplications with a weight in the inner loop
        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / w * RENDER_DIVISION;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / w * RENDER_DIVISION;

        // real world coordinates of the leftmost column. This will be updated as we step to the right.
        float floorX = POS_X + rowDistance * rayDirX0;
        float floorY = POS_Y + rowDistance * rayDirY0;

        for(int x = odd; x < w; x+=RENDER_DIVISION)
        {
            // the cell coord is simply got from the integer parts of floorX and floorY
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);

            // get the texture coordinate from the fractional part
            int tx = (int)(TEXTURE_WIDTH * (floorX - cellX)) & (TEXTURE_WIDTH - 1);
            int ty = (int)(TEXTURE_HEIGHT * (floorY - cellY)) & (TEXTURE_HEIGHT - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            //canvas.setRGB(x, y, map.getFloor().getColor(tx, ty));
            //canvas.setRGB(x, h-y-1, map.getCeiling().getColor(tx, ty));
            //getColor(tx, texX, texY);
            setPixel(screen, x, y, getColor(getFloorTexture(cellX, cellY), tx, ty));
            setPixel(screen, x, h-y-1, getColor(getCeilingTexture(cellX, cellY), tx, ty));
        }
    }
}
void renderSprites(Tigr* screen, int w, int h)
{
    Sprite* sp;
    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < SPRITE_COUNT; i++)
    {
        //translate sprite position to relative to camera
        sp = getSprite(spriteOrder[i]);
        float spriteX = sp->pos->x - POS_X;
        float spriteY = sp->pos->y - POS_Y;

        //transform sprite with the inverse camera matrix
        // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
        // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
        // [ planeY   dirY ]                                          [ -planeY  planeX ]

        float invDet = 1.0f / (PLANE_X * DIR_Y - DIR_X * PLANE_Y); //required for correct matrix multiplication

        float transformX = invDet * (DIR_Y * spriteX - DIR_X * spriteY);
        float transformY = invDet * (-PLANE_Y * spriteX + PLANE_X * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

        int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));

        //calculate height of the sprite on screen
        int spriteHeight = abs((int)(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
        //calculate lowest and highest pixel to fill in current stripe
        int drawStartY = -spriteHeight / 2 + h / 2;
        if(drawStartY < 0) drawStartY = 0;
        int drawEndY = spriteHeight / 2 + h / 2;
        if(drawEndY >= h) drawEndY = h - 1;

        //calculate width of the sprite
        int spriteWidth = abs( (int)(h / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if(drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if(drawEndX >= w) drawEndX = w - 1;


        Texture* tx = getTexture(sp->tx);
        //loop through every vertical stripe of the sprite on screen
        for(int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            int texX = (int)((stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXTURE_WIDTH / spriteWidth);
            //the conditions in the if are:
            //1) it's in front of camera plane so you don't see things behind you
            //2) it's on the screen (left)
            //3) it's on the screen (right)
            //4) ZBuffer, with perpendicular distance
            if(transformY > 0 && stripe > 0 && stripe < w && transformY < zBuff[stripe])
            {
                for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
                {
                    int d = (y) * 256 - h * 128 + spriteHeight * 128;
                    int texY = ((d * TEXTURE_HEIGHT) / spriteHeight) / 256;
                    TPixel* clr = getColor(tx, texX, texY);
                    if(clr->r > 0 || clr->g > 0 || clr->b > 0)
                        setPixel(screen, stripe, y, clr);
                }
            }
        }
    }
}
void render(Tigr* screen)
{
    odd = (odd+1)%RENDER_DIVISION;

    renderFloorCeiling(screen, screen->w, screen->h);
    renderWalls(screen, screen->w, screen->h);
    renderSprites(screen, screen->w, screen->h);
}












