#include "player.h"

Player::Player(std::string n) {
    name = n;
    level = 1;
}

void Player::levelUp() {
    ++level;
    std::cout << level << "\n";
}