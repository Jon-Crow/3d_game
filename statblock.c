#include <stddef.h>
#include <stdlib.h>

#include "statblock.h"

Stat* new_stat(char name[MAX_NAME_SIZE], int val, int maxVal)
{
    Stat* stat = malloc(sizeof(Stat));
    if(stat == NULL)
        return NULL;

    for(int i = 0; i < MAX_NAME_SIZE; i++)
        stat->name[i] = name[i];
    stat->val    = val;
    stat->maxVal = maxVal;
    return stat;
}
void free_stat(Stat* stat)
{
    free(stat);
}
StatBlock* new_statblock(int maxHP)
{
    StatBlock* stats = malloc(sizeof(StatBlock));
    if(stats == NULL)
        return NULL;

    stats->stats[STAT_HP] = new_stat("Health", maxHP, maxHP);
    return stats;
}
void free_statblock(StatBlock* stats)
{
    for(int i = 0; i < STAT_COUNT; i++)
        free_stat(stats->stats[i]);
    free(stats);
}
int validStat(int stat)
{
    return stat >= 0 && stat < STAT_COUNT;
}
int getStat(StatBlock* stats, int stat)
{
    if(validStat(stat))
        return stats->stats[stat]->val;
    return -1;
}
int getStatMax(StatBlock* stats, int stat)
{
    if(validStat(stat))
        return stats->stats[stat]->maxVal;
    return -1;
}
float getStatPercent(StatBlock* stats, int stat)
{
    if(validStat(stat))
        return (float)stats->stats[stat]->val/stats->stats[stat]->maxVal;
    return -1.0f;
}
void damage(StatBlock* stats, int amnt)
{
    int* hp = &(stats->stats[STAT_HP]->val);
    *hp -= amnt;
    if(*hp < 0)
        *hp = 0;
}






