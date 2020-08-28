#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "weapon.h"

MeleeWeapon* new_meleeWeapon(Animation* anim, int dmg);
void free_meleeWeapon(void* type);
void actor_meleeWeapon(Weapon* wpn, Player* plyr, Enemy* tar);
void render_meleeWeapon(Tigr* screen, Weapon* weap);

Animation* new_longswordAnimation();

Weapon* new_weapon(char* name, int id, int type)
{
    Weapon* weap = malloc(sizeof(Weapon));
    if(weap == NULL)
        return NULL;

    strncpy(weap->name, name, MAX_WEAPON_NAME_SIZE);
    weap->id = id;
    switch(type)
    {
    case WEAPON_TYPE_MELEE:
        weap->actor    = actor_meleeWeapon;
        weap->render   = render_meleeWeapon;
        weap->freeType = free_meleeWeapon;
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
        weap->type = new_meleeWeapon(new_longswordAnimation(), 10);
        break;
    }
}

MeleeWeapon* new_meleeWeapon(Animation* anim, int dmg)
{
    MeleeWeapon* weap = malloc(sizeof(MeleeWeapon));
    if(weap == NULL)
        return NULL;

    weap->anim   = anim;
    weap->damage = dmg;
    return weap;
}
void free_meleeWeapon(void* type)
{
    MeleeWeapon* weap = (MeleeWeapon*)type;
    free_animation(weap->anim);
    free(weap);
}
void actor_meleeWeapon(Weapon* wpn, Player* plyr, Enemy* tar)
{

}
void render_meleeWeapon(Tigr* screen, Weapon* weap)
{

}

Animation* new_longswordAnimation()
{
    int frames[MAX_ANIMATION_FRAMES];
    frames[0] = BANDIT_IDLE;
    return new_animation(frames, 1, 1, 0);
}





