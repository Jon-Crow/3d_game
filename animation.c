#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "animation.h"

static Texture* animTextures[ANIMATION_TEXTURE_COUNT];

#define INIT_TEXTURES(START,END,PATH) \
    for(int i = START; i < END; i++) \
    { \
        sprintf(pathBuff, PATH, i-START); \
        init_texture(animTextures[i], pathBuff); \
    }

void init_animationTextures()
{
    char pathBuff[128];
    for(int i = 0; i < ANIMATION_TEXTURE_COUNT; i++)
        animTextures[i] = new_texture(TEXTURE_WIDTH, TEXTURE_HEIGHT);

    init_texture(animTextures[0], BANDIT_IDLE_PATH);
    INIT_TEXTURES(BANDIT_RUN(0), BANDIT_RUN(RUN_LENGTH), BANDIT_RUN_PATH)
    INIT_TEXTURES(BANDIT_ATTACK(0), BANDIT_ATTACK(ATTACK_LENGTH), BANDIT_ATTACK_PATH)
    INIT_TEXTURES(BANDIT_HURT(0), BANDIT_HURT(HURT_LENGTH), BANDIT_HURT_PATH)
    INIT_TEXTURES(BANDIT_DIE(0), BANDIT_DIE(DIE_LENGTH), BANDIT_DIE_PATH)
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

#define INIT_ANIMATION(LEN,START,TIME,ONESHOT) \
    int frames[MAX_ANIMATION_FRAMES]; \
    for(int i = 0; i < LEN; i++) \
        frames[i] = START+i; \
    return new_animation(frames, LEN, TIME, ONESHOT);


Animation* new_banditIdle()
{
    int frames[MAX_ANIMATION_FRAMES] = {BANDIT_IDLE};
    return new_animation(frames, 1, 0, 1);
}
Animation* new_banditRun()
{
    INIT_ANIMATION(RUN_LENGTH, BANDIT_RUN(0), 0.25f, 0)
}
Animation* new_banditAttack()
{
    INIT_ANIMATION(ATTACK_LENGTH ,BANDIT_ATTACK(0), 0.15f, 1)
}
Animation* new_banditHurt()
{
    INIT_ANIMATION(HURT_LENGTH ,BANDIT_HURT(0), 0.15f, 1)
}
Animation* new_banditDie()
{
    INIT_ANIMATION(DIE_LENGTH ,BANDIT_DIE(0), 0.15f, 1)
}







