#ifndef WEAPON_H
#define WEAPON_H

#include "game.h"
#include "settings.h"
#include "texture.h"

#define WEAPON_TYPE_MELEE (0)
#define WEAPON_TYPE_STAFF (1)

#define WEAPON_COUNT   (2)
#define LONGSWORD_ID   (0)
#define FIRESTAFF_ID   (1)
#define LONGSWORD_NAME ("Longsword")
#define FIRESTAFF_NAME ("Fire Staff")

#define PATH_NOT_FOUND       ("ERR_PATH_NOT_FOUND")
#define LONGSWORD_IDLE_PATH  ("res/textures/weapons/longsword/idle.png")
#define LONGSWORD_SWING_PATH ("res/textures/weapons/longsword/swing.png")
#define LONGSWORD_CD_PATH    ("res/textures/weapons/longsword/cooldown.png")
#define FIRESTAFF_IDLE_PATH  ("res/textures/weapons/firestaff/idle.png")
#define FIRESTAFF_SWING_PATH ("res/textures/weapons/firestaff/swing.png")
#define FIRESTAFF_CD_PATH    ("res/textures/weapons/firestaff/cooldown.png")

#define MAX_WEAPON_NAME_SIZE (32)
#define WEAPON_IMG_SIZE      ((int)(getScreenWidth()/3))

typedef struct sWeapon Weapon;

typedef void (*WeaponActor)(Weapon*, float, int, int);
typedef void (*WeaponRenderer)(Tigr*, Weapon*);
typedef void (*WeaponTypeFreeFunc)(void*);

struct sWeapon
{
    char name[MAX_WEAPON_NAME_SIZE];
    int id;
    WeaponRenderer render;
    WeaponActor actor;
    void* type;
    WeaponTypeFreeFunc freeType;
    float cd;
    float cdDur;
};
typedef struct
{
    int damage;
} MeleeWeapon;

void init_weaponTextures();
void free_weaponTextures();
Weapon* new_weapon(char* name, int id, int type);
void free_weapon(Weapon* weap);
void init_weapon(Weapon* weap);

#endif // WEAPON_H
