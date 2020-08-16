#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "game.h"
#include "map.h"
#include "texture.h"
#include "tigr.h"

#define SCREEN_WIDTH  (800)
#define SCREEN_HEIGHT (600)

float randFloat()
{
    return (float)rand()/(float)RAND_MAX;
}
long timeInMillis(long sec, long usec)
{
    long s1 = (long)(sec) * 1000;
    long s2 = (usec / 1000);
    return s1 + s2;
}
int main(int argc, char *argv[])
{
    Tigr* screen;
    Tigr* fontImg;
    float delta, fpsTime = 0;
    int frameCount = 0, fps;
    char fpsStr[16];

    printf("about to initialize my shit\n");

    fontImg = tigrLoadImage("res/fonts/main.png");
    TigrFont *mainFont = tigrLoadFont(fontImg, 1252);

    init_textures();
    printf("textures initialized\n");
    init_map();
    printf("map initialized\n");
    init_game();
    printf("game initialized\n");
    screen = tigrWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello", 0);

    printf("Shit has been initialized\n");

    while (!tigrClosed(screen))
    {
        delta = tigrTime();
        update(screen, delta);
        render(screen);

        fpsTime += delta;
        frameCount++;
        if(fpsTime > 1)
        {
            fps = frameCount;
            frameCount = 0;
            fpsTime = 0;
        }
        sprintf(fpsStr, "fps: %d", fps);
        tigrPrint(screen, mainFont, 50, 50, *getColor(getTexture(TEXTURE_STONE), 0, 0), fpsStr);

        tigrUpdate(screen);
    }

    printf("about to free my shit\n");

    free_game();
    printf("game freed\n");
    free_map();
    printf("map freed\n");
    free_textures();
    printf("textures freed\n");
    tigrFree(fontImg);
    tigrFreeFont(mainFont);
    tigrFree(screen);

    printf("Shit has been freed\n");
    return 0;
}
