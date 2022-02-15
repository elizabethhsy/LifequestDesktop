#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>

#include "quest.h"

class Player {
    public:
        int id;
        std::string name;
        int level = 1;
        int experience = 0;
        int strength = 1;
        int agility = 1;
        int vitality = 1;
        int intelligence= 1;
        int wisdom = 1;
        int willpower = 1;
        int fame = 0;

        std::vector<QuestChain> questChains;

        // constructors
        Player() = default;
        Player(const std::string& name);
        Player(const int& database_id);

        // class methods
        void acceptQuestChain(QuestChain &questChain);
        void levelUp();
        void save();
};

#endif