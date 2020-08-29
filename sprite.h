#ifndef SPRITE_H
#define SPRITE_H

#include "vectors.h"
#include "texture.h"
#include "statblock.h"
#include "animation.h"

#define SPRITE_TYPE_DECORATION (0)
#define SPRITE_TYPE_ENEMY      (1)
#define SPRITE_TYPE_SPELL      (2)

#define ENEMY_VISION_DIST      (10.0f)
#define ENEMY_MIN_DIST         (0.5f)
#define ENEMY_ATTACK_DIST      (0.75f)
#define ENEMY_SPEED            (1.5f)

#define MAX_ENEMY_ANIMATIONS   (5)
#define ENEMY_ANIMATION_IDLE   (0)
#define ENEMY_ANIMATION_RUN    (1)
#define ENEMY_ANIMATION_ATTACK (2)
#define ENEMY_ANIMATION_HURT   (3)
#define ENEMY_ANIMATION_DIE    (4)

#define ENEMY_ID_BANDIT        (0)
#define ENEMY_ID_BAT           (1)

#define SPELL_TYPE_FIRE        (0)

typedef struct sSprite Sprite;
typedef struct sEnemy  Enemy;
typedef struct sSpell  Spell;

typedef void (*SpriteActor)(Sprite*, int, float);
typedef void (*SpriteTypeFreeFunc)(void *);
typedef void (*EnemyAttack)(Enemy*, StatBlock*);

struct sSprite
{
    Vector2f* pos;
    Vector2f* dir;
    Texture* tx;
    SpriteActor actor;
    SpriteTypeFreeFunc freeType;
    void* type;
};
struct sEnemy
{
    int typeID;
    StatBlock* stats;
    float cd;
    float cdTime;
    EnemyAttack attack;
    Animation* anims[MAX_ENEMY_ANIMATIONS];
    int curAnim;
};
struct sSpell
{
    int damage;
    int type;
    float speed;
};

Sprite* new_sprite(float x, float y, Texture* tx, SpriteActor actor, SpriteTypeFreeFunc freeType, void* type);
void free_sprite(Sprite* sp);
Enemy* new_enemy(int enemyID);
void free_enemy(Enemy* en);
Spell* new_spell(int damage, int type, float speed);
void free_spell(Spell* spell);
Animation* getEnemyAnimation(Enemy* en);
void setEnemyAnimation(Enemy* en, int anim);
int enemyAttacking(Enemy* en);
int enemyHurting(Enemy* en);
int enemyDying(Enemy* en);
void damageEnemy(Enemy* en, int amnt);
int isDecoration(Sprite* sp);
int isEnemy(Sprite* sp);
int isSpell(Sprite* sp);

#endif // SPRITE_H
