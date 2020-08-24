#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "animation.h"

static Texture* animTextures[ANIMATION_TEXTURE_COUNT];

void init_animationTextures()
{
    char pathBuff[128];
    for(int i = 0; i < ANIMATION_TEXTURE_COUNT; i++)
        animTextures[i] = new_texture(TEXTURE_WIDTH, TEXTURE_HEIGHT);

    init_texture(animTextures[0], BANDIT_IDLE_PATH);
    for(int i = BANDIT_RUN(0); i < BANDIT_RUN(RUN_LENGTH); i++)
    {
        sprintf(pathBuff, BANDIT_RUN_PATH, i-BANDIT_RUN(0));
        init_texture(animTextures[i], pathBuff);
    }
    for(int i = BANDIT_ATTACK(0); i < BANDIT_ATTACK(ATTACK_LENGTH); i++)
    {
        sprintf(pathBuff, BANDIT_ATTACK_PATH, i-BANDIT_ATTACK(0));
        init_texture(animTextures[i], pathBuff);
    }
}
void free_animationTextures()
{
    for(int i = 0; i < ANIMATION_TEXTURE_COUNT; i++)
        free_texture(animTextures[i]);
}
Animation* new_animation(int frames[MAX_ANIMATION_FRAMES], int frameCount, float frameDur, int oneShot)
{
    Animation* anim = malloc(sizeof(Animation));
    if(anim == NULL)
        return NULL;

    for(int i = 0; i < MAX_ANIMATION_FRAMES; i++)
        anim->frames[i] = frames[i];
    anim->frameCount = frameCount;
    anim->frameDur   = frameDur;
    anim->curFrame   = 0;
    anim->frameTime  = 0;
    anim->oneShot    = oneShot;
    anim->done       = 0;
    return anim;
}
void free_animation(Animation* anim)
{
    if(anim != NULL)
        free(anim);
}
void updateAnimation(Animation* anim, float delta)
{
    if(anim->done)
        return;
    anim->frameTime += delta;
    if(anim->frameTime >= anim->frameDur)
    {
        anim->frameTime -= anim->frameDur;
        anim->curFrame++;
        if(anim->curFrame >= anim->frameCount)
        {
            if(anim->oneShot)
            {
                anim->curFrame--;
                anim->done = 1;
            }
            else
                anim->curFrame = 0;
        }
    }
}
Texture* getAnimationFrame(Animation* anim)
{
    return animTextures[anim->frames[anim->curFrame]];
}

Animation* new_banditIdle()
{
    int frames[MAX_ANIMATION_FRAMES] = {BANDIT_IDLE};
    return new_animation(frames, 1, 0, 1);
}
Animation* new_banditRun()
{
    int frames[MAX_ANIMATION_FRAMES];
    for(int i = 0; i < RUN_LENGTH; i++)
        frames[i] = BANDIT_RUN(i);
    return new_animation(frames, RUN_LENGTH, 0.25f, 0);
}
Animation* new_banditAttack()
{
    int frames[MAX_ANIMATION_FRAMES];
    for(int i = 0; i < ATTACK_LENGTH; i++)
        frames[i] = BANDIT_ATTACK(i);
    return new_animation(frames, ATTACK_LENGTH, 0.15f, 1);
}







