#if defined(__cplusplus)
  extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "game.h"
#include "map.h"
#include "texture.h"
#include "tigr.h"
#include "gamestate.h"
#include "colors.h"
#include "menu.h"
#include "settings.h"
#include "weapon.h"

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
    TigrFont* mainFont;
    float delta, fpsTime = 0;
    int frameCount = 0, fps;
    char fpsStr[16];

    printf("about to initialize my shit\n");

    loadSettings();

    fontImg = tigrLoadImage("res/fonts/main.png");
    mainFont = tigrLoadFont(fontImg, 1252);

    init_colors();
    printf("colors initialized\n");
    init_textures();
    printf("textures initialized\n");
    init_map();
    printf("map initialized\n");
    init_game();
    printf("game initialized\n");
    screen = tigrWindow(getScreenWidth(), getScreenHeight(), "Hello", 0);
    sprintf(fpsStr, "--");

    printf("Shit has been initialized\n");

    setGameState(updateMenu, renderMenu);

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
            sprintf(fpsStr, "fps: %d", fps);
        }
        tigrPrint(screen, mainFont, 50, 50, *color(COLOR_WHITE), fpsStr);

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
    tigrFree(screen);
    free_colors();
    printf("colors freed\n");

    saveSettings();

    printf("Shit has been freed\n");
    return 0;
}


#if defined(__cplusplus)
  }
#endif
