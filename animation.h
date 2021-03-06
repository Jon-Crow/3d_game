#ifndef ANIMATION_H
#define ANIMATION_H

#include "texture.h"

#define MAX_ANIMATION_FRAMES (16)

#define BANDIT_IDLE_PATH   ("res/textures/animations/bandit/idle.png")
#define BANDIT_RUN_PATH    ("res/textures/animations/bandit/run%d.png")
#define BANDIT_ATTACK_PATH ("res/textures/animations/bandit/attack%d.png")
#define BANDIT_HURT_PATH   ("res/textures/animations/bandit/hurt%d.png")
#define BANDIT_DIE_PATH    ("res/textures/animations/bandit/die%d.png")
#define BAT_IDLE_PATH      ("res/textures/animations/bat/idle.png")
#define BAT_RUN_PATH       ("res/textures/animations/bat/run%d.png")
#define BAT_ATTACK_PATH    ("res/textures/animations/bat/attack%d.png")
#define BAT_HURT_PATH      ("res/textures/animations/bat/hurt%d.png")
#define BAT_DIE_PATH       ("res/textures/animations/bat/die%d.png")

#define ANIMATION_TEXTURE_COUNT (34)
#define RUN_LENGTH       (4)
#define ATTACK_LENGTH    (4)
#define HURT_LENGTH      (4)
#define DIE_LENGTH       (4)
#define BANDIT_IDLE      (0)
#define BANDIT_RUN(I)    (1+I)
#define BANDIT_ATTACK(I) (5+I)
#define BANDIT_HURT(I)   (9+I)
#define BANDIT_DIE(I)    (13+I)
#define BAT_IDLE         (17)
#define BAT_RUN(I)       (18+I)
#define BAT_ATTACK(I)    (22+I)
#define BAT_HURT(I)      (26+I)
#define BAT_DIE(I)       (30+I)


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
Animation* new_banditHurt();
Animation* new_banditDie();

Animation* new_batIdle();
Animation* new_batRun();
Animation* new_batAttack();
Animation* new_batHurt();
Animation* new_batDie();

#endif // ANIMATION_H
