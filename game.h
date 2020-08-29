#ifndef GAME_H
#define GAME_H

#include "tigr.h"
#include "vectors.h"
#include "sprite.h"
#include "statblock.h"
#include "weapon.h"
#include "inventory.h"
#include "quest.h"

#define MOUSE_LEFT   (0x001)
#define MOUSE_MIDDLE (0x010)
#define MOUSE_RIGHT  (0x100)

typedef struct sWeapon Weapon;
typedef struct sInventory Inventory;

typedef struct
{
    Vector2f* pos;
    Vector2f* dir;
    Vector2f* plane;
    StatBlock* stats;
    Weapon* weap;
    Inventory* inv;
    QuestBook* book;
} Player;

void init_game();
void free_game();
Sprite* getOrderedSprite(int spriteI);
int getDistanceFromPlayer(int spriteI);
Player* getPlayer();
Vector2f* getPlayerPos();
Vector2f* getPlayerDir();
void updateGame(Tigr* screen, float delta);
void renderGame(Tigr* screen);

void actor_decoration(Sprite* sp, int id, float delta);
void actor_enemy(Sprite* sp, int id, float delta);
void actor_spell(Sprite* sp, int id, float delta);
void freeType_decoration(void* type);
void freeType_enemy(void* type);
void freeType_spell(void* type);

void attack_bandit(Enemy* bandit, StatBlock* tar);

#endif // GAME_H
