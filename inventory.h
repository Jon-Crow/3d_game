#ifndef INVENTORY_H
#define INVENTORY_H

#include "weapon.h"

#define MAX_WEAPON_COUNT (32)

typedef struct sInventory Inventory;
typedef struct sWeapon Weapon;

struct sInventory
{
    int gold;
    Weapon* wpns[MAX_WEAPON_COUNT];
    int wpnCount;
};

Inventory* new_inventory();
void free_inventory(Inventory* inv);
void addWeapon(Inventory* inv, Weapon* wpn);
void removeWeapon(Inventory* inv, Weapon* wpn);

#endif // INVENTORY_H
