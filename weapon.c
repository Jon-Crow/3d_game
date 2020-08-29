#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "sprite.h"
#include "weapon.h"
#include "vectors.h"
#include "map.h"

#define PATH_BUFFER_SIZE (128)

MeleeWeapon* new_meleeWeapon(int dmg);
void free_meleeWeapon(void* type);
void actor_meleeWeapon(Weapon* wpn, float delta, int mBtns, int mBtns_prev);
void free_staffWeapon(void* type);
void actor_staffWeapon(Weapon* wpn, float delta, int mBtns, int mBtns_prev);
void render_defaultWeapon(Tigr* screen, Weapon* weap);

static Tigr* weaponIdle[WEAPON_COUNT];
static Tigr* weaponSwing[WEAPON_COUNT];
static Tigr* weaponCD[WEAPON_COUNT];

void getWeaponPaths(int weapID, char idlePath[PATH_BUFFER_SIZE], char swingPath[PATH_BUFFER_SIZE], char cdPath[PATH_BUFFER_SIZE])
{
    switch(weapID)
    {
    case LONGSWORD_ID:
        strncpy(idlePath, LONGSWORD_IDLE_PATH, PATH_BUFFER_SIZE);
        strncpy(swingPath, LONGSWORD_SWING_PATH, PATH_BUFFER_SIZE);
        strncpy(cdPath, LONGSWORD_CD_PATH, PATH_BUFFER_SIZE);
        break;
    case FIRESTAFF_ID:
        strncpy(idlePath, FIRESTAFF_IDLE_PATH, PATH_BUFFER_SIZE);
        strncpy(swingPath, FIRESTAFF_SWING_PATH, PATH_BUFFER_SIZE);
        strncpy(cdPath, FIRESTAFF_CD_PATH, PATH_BUFFER_SIZE);
        break;
    default:
        strncpy(idlePath, PATH_NOT_FOUND, PATH_BUFFER_SIZE);
        strncpy(swingPath, PATH_NOT_FOUND, PATH_BUFFER_SIZE);
        strncpy(cdPath, PATH_NOT_FOUND, PATH_BUFFER_SIZE);
    }
}
void init_weaponTextures()
{
    printf("weapon image size: %d\n", WEAPON_IMG_SIZE);
    char idle[PATH_BUFFER_SIZE];
    char swing[PATH_BUFFER_SIZE];
    char cd[PATH_BUFFER_SIZE];
    for(int i = 0; i < WEAPON_COUNT; i++)
    {
        getWeaponPaths(i, idle, swing, cd);
        if(strcmp(idle, PATH_NOT_FOUND) != 0 && strcmp(swing, PATH_NOT_FOUND) != 0 && strcmp(cd, PATH_NOT_FOUND) != 0)
        {
            Tigr* idleImg  = tigrLoadImage(idle);
            Tigr* swingImg = tigrLoadImage(swing);
            Tigr* cdImg    = tigrLoadImage(cd);

            weaponIdle[i]  = scaleImage(idleImg, WEAPON_IMG_SIZE, WEAPON_IMG_SIZE);
            weaponSwing[i] = scaleImage(swingImg, WEAPON_IMG_SIZE, WEAPON_IMG_SIZE);
            weaponCD[i]    = scaleImage(cdImg, WEAPON_IMG_SIZE, WEAPON_IMG_SIZE);

            tigrFree(idleImg);
            tigrFree(swingImg);
            tigrFree(cdImg);
        }
    }
}
void free_weaponTextures()
{
    for(int i = 0; i < WEAPON_COUNT; i++)
    {
        tigrFree(weaponIdle[i]);
        tigrFree(weaponSwing[i]);
        tigrFree(weaponCD[i]);
    }
}
Weapon* new_weapon(char* name, int id, int type)
{
    Weapon* weap = malloc(sizeof(Weapon));
    if(weap == NULL)
        return NULL;

    strncpy(weap->name, name, MAX_WEAPON_NAME_SIZE);
    weap->id = id;
    weap->cd = 0;
    switch(type)
    {
    case WEAPON_TYPE_MELEE:
        weap->actor    = actor_meleeWeapon;
        weap->render   = render_defaultWeapon;
        weap->freeType = free_meleeWeapon;
        break;
    case WEAPON_TYPE_STAFF:
        weap->actor    = actor_staffWeapon;
        weap->render   = render_defaultWeapon;
        weap->freeType = free_staffWeapon;
        break;
    default:
        free(weap);
        return NULL;
    }
    init_weapon(weap);
    return weap;
}
void free_weapon(Weapon* weap)
{
    weap->freeType(weap->type);
    free(weap);
}
void init_weapon(Weapon* weap)
{
    switch(weap->id)
    {
    case LONGSWORD_ID:
        weap->type  = new_meleeWeapon(10);
        weap->cdDur = 2.0f;
        break;
    case FIRESTAFF_ID:
        weap->type  = new_spell(15, SPELL_TYPE_FIRE, 0.5f);
        weap->cdDur = 2.5f;
        break;
    }
}

MeleeWeapon* new_meleeWeapon(int dmg)
{
    MeleeWeapon* weap = malloc(sizeof(MeleeWeapon));
    if(weap == NULL)
        return NULL;

    weap->damage = dmg;
    return weap;
}
void free_meleeWeapon(void* type)
{
    MeleeWeapon* weap = (MeleeWeapon*)type;
    free(weap);
}
void actor_meleeWeapon(Weapon* wpn, float delta, int mBtns, int mBtns_prev)
{
    if(wpn->cd > 0)
    {
        wpn->cd -= delta;
        return;
    }
    if(mBtns&MOUSE_LEFT && !(mBtns_prev&MOUSE_LEFT))
    {
        wpn->cd = wpn->cdDur;
        Sprite* sp;
        for(int i = 0; i < getSpriteCount(); i++)
        {
            sp = getOrderedSprite(i);
            if(isEnemy(sp))
            {
                if(getDistanceFromPlayer(i) <= ENEMY_ATTACK_DIST)
                {
                    float reqDir = directionTo(getPlayerPos(), sp->pos);
                    float minDir = reqDir-0.2f;
                    float maxDir = reqDir+0.2f;
                    float dir    = direction(getPlayerDir());
                    if(minDir < -M_PI)
                        minDir = M_PI-minDir;
                    if(maxDir > M_PI)
                        maxDir = maxDir - M_PI;
                    if(minDir > maxDir)
                    {
                        float temp = maxDir;
                        maxDir = minDir;
                        minDir = temp;
                    }
                    if(dir > minDir && dir < maxDir)
                    {
                        damageEnemy((Enemy*)sp->type, 5);
                        return;
                    }
                }
            }
        }
    }
}
void free_staffWeapon(void* type)
{
    free_spell((Spell*)type);
}
void actor_staffWeapon(Weapon* wpn, float delta, int mBtns, int mBtns_prev)
{
    if(wpn->cd > 0)
    {
        wpn->cd -= delta;
        return;
    }
    if(mBtns&MOUSE_LEFT && !(mBtns_prev&MOUSE_LEFT))
    {
        Spell* spell = (Spell*)wpn->type;
        Spell* spellCp = new_spell(0, 0, 0);
        memcpy(spellCp, spell, sizeof(Spell));

        Vector2f* pos = getPlayerPos();
        Vector2f* dir = getPlayerDir();

        Sprite* sp = addSprite(pos->x, pos->y, TEXTURE_FIREBALL, actor_spell, freeType_spell, spellCp);
        memcpy(sp->dir, dir, sizeof(Vector2f));

        wpn->cd = wpn->cdDur;
    }
}
void render_defaultWeapon(Tigr* screen, Weapon* weap)
{
    if(weap->id < 0 || weap->id >= WEAPON_COUNT)
        return;
    Tigr* img;
    if(weap->cd > weap->cdDur*0.9f)
        img = weaponSwing[weap->id];
    else if(weap->cd > 0)
        img = weaponCD[weap->id];
    else
        img = weaponIdle[weap->id];
    tigrBlitAlpha(screen,img,getScreenWidth()-WEAPON_IMG_SIZE,getScreenHeight()-WEAPON_IMG_SIZE,
                  0,0,WEAPON_IMG_SIZE,WEAPON_IMG_SIZE,1.0f);
}








