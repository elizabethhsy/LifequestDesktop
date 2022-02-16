#include "quest.h"

QuestChain::QuestChain(const std::string& t, const std::string& d) {
    title = t;
    description = d;
    // description = "this is a test description";

    QSqlQuery query;
    query.exec("INSERT INTO questchain (title, description) VALUES (" + toQString(title) + "," + toQString(description) + ");"); // create row in database
    id = query.lastInsertId().toInt();
    save();

    questChains.push_back(*this); // push itself back onto questChains
}

QuestChain::QuestChain(const int& database_id) {
    QSqlQuery query;
    query.exec("SELECT * from questchain WHERE id = " + toQString(database_id));
    while (query.next()) {
        id = database_id;
        title = query.value(1).toString().toStdString();
        description = query.value(2).toString().toStdString();
        // std::cout << "description: " << description << "\n";
        // qDebug() << query.value(1).toString();
    }

    questChains.push_back(*this); // push itself back onto questChains
}

int QuestChain::returnId() {
    return id;
}

void QuestChain::save() {
    QSqlQuery query;
    query.exec("UPDATE questchain SET title = " + toQString(title)
    + ",description = " + toQString(description)
    + " WHERE id = " + toQString(id));
}

// create objects from the database
std::vector<QuestChain> createQuestChains() {
    std::vector<QuestChain> questChains;
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM questchain");
    if (query.next()) {
        int count = query.value(0).toInt();
        // std::cout << "count: " << count << "\n";
        for(int i=1; i<=count; i++) {
            QuestChain questChain(i);
            questChains.push_back(questChain);
        }
    }

    // std::cout << "number of quest chains: " << questChains.size() << "\n";

    return questChains;
}

Quest::Quest(QuestChain &parentQuestChain, std::string &title, std::string &description) {
    parentQuestChain = parentQuestChain;
    title = title;
    description = description;

    int questChainId = parentQuestChain.returnId();

    QSqlQuery query;
    query.exec("INSERT INTO quest (questchain_id, title, description) VALUES (" + toQString(questChainId) + "," + toQString(title) + "," + toQString(description) + ");"); // create row in database
    id = query.lastInsertId().toInt();
    save();

    quests.push_back(*this);
}

Quest::Quest(const int& database_id) {
    QSqlQuery query;
    query.exec("SELECT * from quest WHERE id = " + toQString(database_id));
    while (query.next()) {
        id = database_id;
        title = query.value(1).toString().toStdString();
        description = query.value(2).toString().toStdString();
        // std::cout << "description: " << description << "\n";
        // qDebug() << query.value(1).toString();
    }

    quests.push_back(*this); // push itself back onto questChains
}

void Quest::save() {
    int questChainId = parentQuestChain.returnId();

    QSqlQuery query;
    query.exec("UPDATE questchain SET questchain_id = " + toQString(questChainId)
    + ",title = " + toQString(title)
    + ",description = " + toQString(description)
    + " WHERE id = " + toQString(id));
}

std::vector<Quest> createQuests() {
    std::vector<Quest> quests;
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM quest");
    if (query.next()) {
        int count = query.value(0).toInt();
        // std::cout << "count: " << count << "\n";
        for(int i=1; i<=count; i++) {
            Quest quest(i);
            quests.push_back(quest);
        }
    }

    // std::cout << "number of quests: " << quests.size() << "\n";

    return quests;
}