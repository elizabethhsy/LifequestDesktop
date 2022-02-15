#ifndef QUEST_H
#define QUEST_H

class QuestChain {
    public:
        int id;
        std::string title;
        std::string description;

        QuestChain() = default;
        QuestChain(const std::string& title, const std::string &description);

        void save();
};

class Quest {
    public:
        int id;
        std::string title;
        std::string description;

        QuestChain parentQuestChain;
        Quest *previousQuest; // pointer due to forward declaration

        Quest(QuestChain &parentQuestChain, std::string &title, std::string &description);

        void save();
};

#endif