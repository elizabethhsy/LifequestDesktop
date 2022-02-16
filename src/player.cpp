#include "database.h"
#include "player.h"

// create player object based on name
Player::Player(const std::string& n) {
    name = n;

    // add player to the database and save its database id
    QSqlQuery query;
    query.exec("INSERT INTO player (name) VALUES (" + toQString(name) + ");"); // create row in database
    id = query.lastInsertId().toInt();
    save(); // update row in database with initial values
}

// download player data from database based on id
Player::Player(const int& database_id) {
    QSqlQuery query;
    query.exec("SELECT * from player WHERE id = " + toQString(database_id));
    while (query.next()) {
        id = database_id;
        name = query.value(1).toString().toStdString();
        level = query.value(2).toInt();
        experience = query.value(3).toInt();
        strength = query.value(4).toInt();
        agility = query.value(5).toInt();
        vitality = query.value(6).toInt();
        intelligence = query.value(7).toInt();
        wisdom = query.value(8).toInt();
        willpower = query.value(9).toInt();
        fame = query.value(10).toInt();
        // qDebug() << query.value(1).toString();
    }
}

void Player::acceptQuestChain(QuestChain& questChain) {
    QSqlQuery query;
    query.exec("INSERT INTO accept_questchain (player_id, questchain_id, quest_index) VALUES (" + toQString(id) + "," + toQString(questChain.id) + ",1);"); // create row in database
}

void Player::levelUp() {
    ++level;
    std::cout << "Level: " << level << "\n";
    save();
}

void Player::save() {
    QSqlQuery query;
    query.exec("UPDATE player SET level = " + toQString(level)
    + ",experience = " + toQString(experience)
    + ",strength = " + toQString(strength)
    + ",agility = " + toQString(agility)
    + ",vitality = " + toQString(vitality)
    + ",intelligence = " + toQString(intelligence)
    + ",wisdom = " + toQString(wisdom)
    + ",willpower = " + toQString(willpower)
    + ",fame = " + toQString(fame)
    + " WHERE id = " + toQString(id));
}