#include <stddef.h>
#include <stdlib.h>

#include "sprite.h"
#include "game.h"

Sprite* new_sprite(float x, float y, Texture* tx, void (*actor)(Sprite*, int, float), void (*freeType)(void*), void* type)
{
    Sprite* sp = malloc(sizeof(Sprite));
    if(sp == NULL)
        return NULL;
    sp->pos      = new_vector2f(x, y);
    sp->dir      = new_vector2f(1, 0);
    sp->tx       = tx;
    sp->actor    = actor;
    sp->freeType = freeType;
    sp->type     = type;
    return sp;
}
void free_sprite(Sprite* sp)
{
    free_vector2f(sp->pos);
    free_vector2f(sp->dir);
    sp->freeType(sp->type);
    free(sp);
}
Enemy* new_enemy(int enemyID)
{
    Enemy* en = malloc(sizeof(Enemy));
    if(en == NULL)
        return NULL;

    Animation* anims[MAX_ENEMY_ANIMATIONS];
    int maxHP;
    float cdTime;
    void (*attack)(Enemy*, StatBlock*);

    en->typeID = enemyID;

    switch(enemyID)
    {
    case ENEMY_ID_BANDIT:
        anims[ENEMY_ANIMATION_IDLE]   = new_banditIdle();
        anims[ENEMY_ANIMATION_RUN]    = new_banditRun();
        anims[ENEMY_ANIMATION_ATTACK] = new_banditAttack();
        maxHP = 50;
        cdTime = 3;
        attack = attack_bandit;
        break;
    default:
        return en;
    }

    en->stats   = new_statblock(maxHP);
    en->cdTime  = cdTime;
    en->cd      = 0;
    en->attack  = attack;
    en->curAnim = 0;
    for(int i = 0; i < MAX_ENEMY_ANIMATIONS; i++)
        en->anims[i] = anims[i];
    return en;
}
void free_enemy(Enemy* en)
{
    for(int i = 0; i < MAX_ENEMY_ANIMATIONS; i++)
        free_animation(en->anims[i]);
    free_statblock(en->stats);
    free(en);
}
Animation* getEnemyAnimation(Enemy* en)
{
    return en->anims[en->curAnim];
}
void setEnemyAnimation(Enemy* en, int anim)
{
    if(anim < 0 || anim >= MAX_ENEMY_ANIMATIONS)
        return;
    if(en->anims[anim]->oneShot)
    {
        en->anims[anim]->done = 0;
        en->anims[anim]->curFrame = 0;
    }
    en->curAnim = anim;
}
int enemyAttacking(Enemy* en)
{
    if(en->curAnim == ENEMY_ANIMATION_ATTACK)
    {
        return getEnemyAnimation(en)->done == 0;
    }
    return 0;
}




