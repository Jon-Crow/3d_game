#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "quest.h"

Quest* new_quest(char name[QUEST_NAME_LENGTH], char desc[QUEST_DESC_LENGTH], int type, int progMax, int meta)
{
    Quest* quest = malloc(sizeof(Quest));
    if(quest == NULL)
        return NULL;

    strncpy(quest->name, name, QUEST_NAME_LENGTH);
    strncpy(quest->desc, desc, QUEST_DESC_LENGTH);
    quest->type    = type;
    quest->prog    = 0;
    quest->progMax = progMax;
    quest->meta    = meta;

    return quest;
}
void free_quest(Quest* quest)
{
    free(quest);
}
QuestBook* new_questBook()
{
    QuestBook* book = malloc(sizeof(QuestBook));
    if(book == NULL)
        return NULL;

    book->questCount = 0;
    return book;
}
void free_questBook(QuestBook* book)
{
    for(int i = 0; i < book->questCount; i++)
        free_quest(book->quests[i]);
    free(book);
}
void addQuest(QuestBook* book, Quest* quest)
{
    if(book->questCount >= MAX_QUEST_COUNT)
        return;
    book->quests[book->questCount] = quest;
    book->questCount++;
}
void removeQuest(QuestBook* book, Quest* quest)
{
    for(int i = 0; i < book->questCount; i++)
    {
        if(book->quests[i] == quest)
        {
            for(int x = i+1; x < book->questCount; x++)
                book->quests[i-1] = book->quests[i];
            book->questCount--;
            free_quest(quest);
            return;
        }
    }
}
void addProgress(Quest* quest)
{
    if(quest->prog < quest->progMax)
        quest->prog++;
}
void questTriggerKill(QuestBook* book, int enemyID)
{
    Quest* quest;
    for(int i = 0; i < book->questCount; i++)
    {
        quest = book->quests[i];
        if(quest->type == QUEST_TYPE_KILL && quest->meta == enemyID)
            addProgress(quest);
    }
}






