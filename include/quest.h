#ifndef QUEST_H
#define QUEST_H

#include "database.h"

class QuestChain {
    public:
        int id;
        std::string title;
        std::string description;

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
        std::string title;
        std::string description;

        QuestChain parentQuestChain;
        Quest *previousQuest; // pointer due to forward declaration

        // constructors
        Quest(QuestChain &parentQuestChain, std::string &title, std::string &description);
        Quest(const int& database_id);

        // class methods
        void save();
};

extern std::vector<QuestChain> questChains;
std::vector<QuestChain> createQuestChains();

extern std::vector<Quest> quests;
std::vector<Quest> createQuests();

#endif