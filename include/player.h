#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

class Player {
    public:
        std::string name;
        int level;
        int strength;
        int agility;
        int vitality;
        int intelligence;
        int wisdom;
        int willpower;

        Player(std::string name);
        void levelUp();
};

#endif