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

static int odd;

typedef struct
{
    Vector2f* pos;
    Vector2f* dir;
    Vector2f* plane;
} Player;

static Player* plyr;

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
    if(clr == NULL)
    {
        printf("NULL clr! (%d, %d)\n", x, y);
        return;
    }
    if( (x >= 0 && x < screen->w) && (y >= 0 && y < screen->h) )
    {
        TPixel* px = &(screen->pix[y*screen->w+x]);
        if(px == NULL)
        {
            printf("NULL px! (%d, %d)\n", x, y);
            return;
        }
        px->r = clr->r;
        px->g = clr->g;
        px->b = clr->b;
    }
    else
        printf("set pixel (%d, %d)\n", x, y);
}
void move(float spd)
{
    POS_X += DIR_X*spd;
    POS_Y += DIR_Y*spd;
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
void update(Tigr* screen, float delta)
{
    if(tigrKeyHeld(screen, 'W'))
        move(delta*2);
    if(tigrKeyHeld(screen, 'S'))
        move(-delta*2);
    if(tigrKeyHeld(screen, 'A'))
        rotate(delta*2);
    if(tigrKeyHeld(screen, 'D'))
        rotate(-delta*2);
}
void render(Tigr* screen)
{
    int w = screen->w,
        h = screen->h;

    odd = (odd ? 0 : 1);

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
        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / w * 2;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / w * 2;

        // real world coordinates of the leftmost column. This will be updated as we step to the right.
        float floorX = POS_X + rowDistance * rayDirX0;
        float floorY = POS_Y + rowDistance * rayDirY0;

        for(int x = odd; x < w; x+=2)
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
            setPixel(screen, x, y, getColor(getFloorTexture(), tx, ty));
            setPixel(screen, x, h-y-1, getColor(getCeilingTexture(), tx, ty));
        }
    }

    //RENDER WALLS
    for(int x = odd; x < w; x+=2)
    {
        //calculate ray position and direction
        float camX = 2.0f * x / w - 1; //x-coordinate in camera space
        float rayDirX = DIR_X + PLANE_X * camX;
        float rayDirY = DIR_Y + PLANE_Y * camX;

        //which box of the map we're in
        int mapX = (int)floor(POS_X);
        int mapY = (int)floor(POS_Y);

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

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

        double perpWallDist;
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
        double wallX; //where exactly the wall was hit
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
        double step = 1.0 * TEXTURE_HEIGHT / lineHeight;
        // Starting texture coordinate
        double texPos = (drawStart - h / 2 + lineHeight / 2) * step;

        for(int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (TEXTURE_HEIGHT - 1);
            texPos += step;
            TPixel* px = getColor(getTextureAt(mapX, mapY), texX, texY);
            setPixel(screen, x, y, px);
        }
    }
}












