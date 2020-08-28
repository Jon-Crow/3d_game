#ifndef WEAPON_H
#define WEAPON_H

#include "game.h"

#define WEAPON_TYPE_MELEE (0)

#define LONGSWORD_ID   (0)
#define LONGSWORD_NAME ("Longsword")

#define MAX_WEAPON_NAME_SIZE (32)

typedef struct sWeapon Weapon;

typedef void (*WeaponActor)(Player*);
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
    Animation* anim;
    int damage;
} MeleeWeapon;

Weapon* new_weapon(char* name, int id, int type);
void free_weapon(Weapon* weap);
void init_weapon(Weapon* weap);

#endif // WEAPON_H
