#ifndef QUEST_H
#define QUEST_H

#include <vector>

#include "database.h"

class Quest;

class QuestChain {
    public:
        int id;

        std::string title;
        std::string description;
        
        std::vector<int> childQuests; // stores database_id of child quests

        // constructors
        QuestChain() = default;
        QuestChain(const std::string& t, const std::string& d);
        QuestChain(const int& database_id);

        // class methods
        int returnId();
        void save();
};

class Quest {
    public:
        int id;
        int questChainIndex;

        std::string title;
        std::string description;

        QuestChain parentQuestChain;
        Quest *previousQuest; // pointer due to forward declaration

        // constructors
        Quest(QuestChain &parentQuestChain, int &questChainIndex, std::string &title, std::string &description);
        Quest(const int& database_id);

        // class methods
        void save();
};

extern std::vector<QuestChain> questChains;
std::vector<QuestChain> createQuestChains();

extern std::vector<Quest> quests;
std::vector<Quest> createQuests();

#endif