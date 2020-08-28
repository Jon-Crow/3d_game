#ifndef STATBLOCK_H
#define STATBLOCK_H

#define MAX_NAME_SIZE (32)
#define STAT_COUNT    (1)
#define STAT_HP       (0)

typedef struct
{
    char name[MAX_NAME_SIZE];
    int val;
    int maxVal;
} Stat;
typedef struct
{
    Stat* stats[STAT_COUNT];
} StatBlock;

Stat* new_stat(char name[MAX_NAME_SIZE], int val, int maxVal);
void free_stat(Stat* stat);
StatBlock* new_statblock(int maxHP);
void free_statblock(StatBlock* stats);
int validStat(int stat);
int getStat(StatBlock* stats, int stat);
int getStatMax(StatBlock* stats, int stat);
float getStatPercent(StatBlock* stats, int stat);
void damage(StatBlock* stats, int amnt);
int isDead(StatBlock* stats);

#endif // STATBLOCK_H
