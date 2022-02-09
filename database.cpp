#include "database.h"

QString quotesql( const QString& s ) {
    return QString("'") + s + QString("'");
}

int addPlayer(std::string name) {
    QString qname = QString::fromStdString(name);
    QSqlQuery query;
    query.exec("INSERT INTO player (name, level, strength, agility, vitality, intelligence, wisdom, willpower, fame) VALUES (" + quotesql(qname) + ", 1, 1, 1, 1, 1, 1, 1, 0);");
    return 0;
}

int initDatabases() {
    QString path = "/Users/Sinon/Dev/LifequestDesktop/data.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query;
    query.exec("CREATE TABLE player (id integer primary key, name varchar(64), level integer, strength integer, agility integer, vitality integer, intelligence integer, wisdom integer, willpower integer, fame integer);");
    query.exec("CREATE TABLE quest (id integer primary key, title varchar(200));");

    return 0;
}