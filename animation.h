#ifndef ANIMATION_H
#define ANIMATION_H

#include "texture.h"

#define MAX_ANIMATION_FRAMES (16)

#define BANDIT_IDLE_PATH   ("res/textures/animations/bandit/idle0.png")
#define BANDIT_RUN_PATH    ("res/textures/animations/bandit/run%d.png")
#define BANDIT_ATTACK_PATH ("res/textures/animations/bandit/attack%d.png")

#define ANIMATION_TEXTURE_COUNT (9)
#define RUN_LENGTH       (4)
#define ATTACK_LENGTH    (4)
#define BANDIT_IDLE      (0)
#define BANDIT_RUN(I)    (1+I)
#define BANDIT_ATTACK(I) (5+I)


typedef struct
{
    int frames[MAX_ANIMATION_FRAMES];
    int frameCount;
    int curFrame;
    float frameDur;
    float frameTime;
    int oneShot;
    int done;
} Animation;

void init_animationTextures();
void free_animationTextures();
Animation* new_animation(int frames[MAX_ANIMATION_FRAMES], int frameCount, float frameDur, int oneShot);
void free_animation(Animation* anim);
void updateAnimation(Animation* anim, float delta);
Texture* getAnimationFrame(Animation* anim);

Animation* new_banditIdle();
Animation* new_banditRun();
Animation* new_banditAttack();

#endif // ANIMATION_H
