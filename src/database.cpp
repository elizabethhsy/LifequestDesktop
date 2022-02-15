#include "database.h"

QString quotesql( const std::string& s ) {
    QString qs = QString::fromStdString(s);
    return QString("'") + qs + QString("'");
}

QString quotesql( const int& i ) {
    std::string s = std::to_string(i);
    return quotesql(s);
}

int initDatabases() {
    QString path = "/Users/Sinon/Dev/LifequestDesktop/data.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();

    return 0;
}

int initTables() {
    QSqlQuery query;
    query.exec("CREATE TABLE player (id integer primary key, name varchar(64), level integer, experience integer, strength integer, agility integer, vitality integer, intelligence integer, wisdom integer, willpower integer, fame integer);");
    query.exec("CREATE TABLE questchain (id integer primary key, title varchar(200), description text);");
    query.exec("CREATE TABLE quest (id integer primary key, questchain_id integer, title varchar(200), description text);");

    return 0;
}

// checks if a sqlite table is empty
bool checkTable(std::string name) {
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name=" + quotesql(name) + ";");
    if (query.next()) {
        int count = query.value(0).toInt();
        // std::cout << "count: " << count << "\n";
        if (count == 0) {
            return false;
        }
        else {
            return true;
        }
    }
}