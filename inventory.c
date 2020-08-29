#include <stddef.h>
#include <stdlib.h>

#include "inventory.h"

Inventory* new_inventory()
{
    Inventory* inv = malloc(sizeof(Inventory));
    if(inv == NULL)
        return NULL;

    inv->gold     = 0;
    inv->wpnCount = 0;

    return inv;
}
void free_inventory(Inventory* inv)
{
    for(int i = 0; i < inv->wpnCount; i++)
        free_weapon(inv->wpns[i]);
    free(inv);
}
void addWeapon(Inventory* inv, Weapon* wpn)
{
    if(inv->wpnCount >= MAX_WEAPON_COUNT)
        return;
    inv->wpns[inv->wpnCount] = wpn;
    inv->wpnCount++;
}
void removeWeapon(Inventory* inv, Weapon* wpn)
{
    for(int i = 0; i < inv->wpnCount; i++)
    {
        if(inv->wpns[i] == wpn)
        {
            for(int x = i+1; x < inv->wpnCount; x++)
                inv->wpns[x-1] = inv->wpns[x];
            inv->wpnCount--;
            free_weapon(wpn);
            return;
        }
    }
}





