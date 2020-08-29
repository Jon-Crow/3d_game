#ifndef QUEST_H
#define QUEST_H

#define QUEST_NAME_LENGTH (32)
#define QUEST_DESC_LENGTH (256)

#define QUEST_TYPE_KILL (0)

#define MAX_QUEST_COUNT (16)

typedef struct
{
    char name[QUEST_NAME_LENGTH];
    char desc[QUEST_DESC_LENGTH];
    int type;
    int prog;
    int progMax;
    int meta;
} Quest;

typedef struct
{
    Quest* quests[MAX_QUEST_COUNT];
    int questCount;
} QuestBook;

Quest* new_quest(char name[QUEST_NAME_LENGTH], char desc[QUEST_DESC_LENGTH], int type, int progMax, int meta);
void free_quest(Quest* quest);
QuestBook* new_questBook();
void free_questBook(QuestBook* book);
void addQuest(QuestBook* book, Quest* quest);
void removeQuest(QuestBook* book, Quest* quest);
void addProgress(Quest* quest);
void questTriggerKill(QuestBook* book, int enemyID);

#endif // QUEST_H
