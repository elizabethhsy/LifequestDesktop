#include "database.h"
#include "quest.h"

QuestChain::QuestChain(const std::string& title, const std::string& description) {
    title = title;
    description = description;

    QSqlQuery query;
    query.exec("INSERT INTO questchain (title, description) VALUES (" + quotesql(title) + "," + quotesql(description) ");"); // create row in database
    id = query.lastInsertId().toInt();
    save();
}

int QuestChain::returnId(QuestChain &questChain) {
    return questChain.id;
}

void QuestChain::save() {
    QSqlQuery query;
    query.exec("UPDATE questchain SET title = " + quotesql(title)
    + ",description = " + quotesql(description));
}

Quest::Quest(QuestChain &parentQuestChain, std::string &title, std::string &description) {
    parentQuestChain = parentQuestChain;
    title = title;
    description = description;

    int questChainId = parentQuestChain.returnId();

    QSqlQuery query;
    query.exec("INSERT INTO quest (questchain_id, title, description) VALUES (" + questChainId + "," + quotesql(name) + "," + quotesql(description) ");"); // create row in database
    id = query.lastInsertId().toInt();
    save();
}

void Quest::save() {
    int questChainId = parentQuestChain.returnId();

    QSqlQuery query;
    query.exec("UPDATE questchain SET questchain_id = " + questChainId
    + ",title = " + quotesql(title)
    + ",description = " + quotesql(description));
}