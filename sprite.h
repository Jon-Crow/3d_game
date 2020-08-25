#ifndef SPRITE_H
#define SPRITE_H

#include "vectors.h"
#include "texture.h"
#include "statblock.h"
#include "animation.h"

#define SPRITE_TYPE_DECORATION (0)
#define SPRITE_TYPE_ENEMY      (1)

#define ENEMY_VISION_DIST      (10.0f)
#define ENEMY_MIN_DIST         (0.5f)
#define ENEMY_ATTACK_DIST      (0.75f)
#define ENEMY_SPEED            (1.5f)

#define MAX_ENEMY_ANIMATIONS   (4)
#define ENEMY_ANIMATION_IDLE   (0)
#define ENEMY_ANIMATION_RUN    (1)
#define ENEMY_ANIMATION_ATTACK (2)
#define ENEMY_ANIMATION_HURT   (3)

#define ENEMY_ID_BANDIT        (0)

typedef struct sSprite Sprite;
typedef struct sEnemy Enemy;

struct sSprite
{
    Vector2f* pos;
    Vector2f* dir;
    Texture* tx;
    void (*actor)(Sprite*, int, float);
    void (*freeType)(void*);
    void* type;
};
struct sEnemy
{
    int typeID;
    StatBlock* stats;
    float cd;
    float cdTime;
    void (*attack)(Enemy*, StatBlock*);
    Animation* anims[MAX_ENEMY_ANIMATIONS];
    int curAnim;
};

Sprite* new_sprite(float x, float y, Texture* tx, void (*actor)(Sprite*, int, float), void (*freeType)(void*), void* type);
void free_sprite(Sprite* sp);
Enemy* new_enemy(int enemyID);
void free_enemy(Enemy* en);
Animation* getEnemyAnimation(Enemy* en);
void setEnemyAnimation(Enemy* en, int anim);
int enemyAttacking(Enemy* en);
int enemyHurting(Enemy* en);
void damageEnemy(Enemy* en, int amnt);
int isDecoration(Sprite* sp);
int isEnemy(Sprite* sp);

#endif // SPRITE_H
