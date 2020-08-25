#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "settings.h"

#define SETTING_SCREEN_HEIGHT ("screen_height")
#define SETTING_SCREEN_WIDTH  ("screen_width")
#define SETTING_RENDER_DIV    ("render_div")
#define TOKEN_BUFFER_SIZE     (32)

static int screenW   = 800,
           screenH   = 600,
           renderDiv = 2;

void loadSettings()
{
    FILE* f = fopen("settings.txt", "r");
    if(f == NULL)
        return;

    char key[TOKEN_BUFFER_SIZE];
    char val[TOKEN_BUFFER_SIZE];
    int c;

    while((c = fgetc(f)) != EOF)
    {
        ungetc(c, f);
        fscanf(f, "%s%s", key, val);
        printf("key: %s, val: %s\n", key, val);
        if(strcmp(key, SETTING_SCREEN_WIDTH) == 0)
        {
            int w = atoi(val);
            if(w <= 0)
                printf("Error: could not read screen width, %d\n", w);
            else
                screenW = w;
        }
        else if(strcmp(key, SETTING_SCREEN_HEIGHT) == 0)
        {
            int h = atoi(val);
            if(h <= 0)
                printf("Error: could not read screen height, %d\n", h);
            else
                screenH = h;
        }
        else if(strcmp(key, SETTING_RENDER_DIV) == 0)
        {
            int rd = atoi(val);
            if(rd <= 0)
                printf("Error: could not read render division, %d\n", rd);
            else
                renderDiv = rd;
        }
    }

    fclose(f);
}
void saveSettings()
{

}
void setScreenSize(int w, int h)
{
    if(w > 0 && h > 0)
    {
        screenW = w;
        screenH = h;
    }
}
int getScreenWidth()
{
    return screenW;
}
int getScreenHeight()
{
    return screenH;
}
void setRenderDivison(int rd)
{
    if(rd > 0)
        renderDiv = rd;
}
int getRenderDivison()
{
    return renderDiv;
}







