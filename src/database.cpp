#include "database.h"

QString toQString( const std::string& s ) {
    QString qs = QString::fromStdString(s);
    return QString("'") + qs + QString("'");
}

QString toQString( const int& i ) {
    std::string s = std::to_string(i);
    return toQString(s);
}

QString toTrimmedQString (const std::string& s) {
    QString trimmed = toQString(s);
    trimmed.remove(0, 1);
    trimmed.chop(1);
    return trimmed;
}

QString toTrimmedQString (const int& i) {
    std::string s = std::to_string(i);
    QString trimmed = toQString(s);
    trimmed.remove(0, 1);
    trimmed.chop(1);
    return trimmed;
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
    query.exec("CREATE TABLE quest (id integer primary key, questchain_id integer, questchain_index integer, title varchar(200), description text);");
    query.exec("CREATE TABLE accept_questchain (id integer primary key, player_id integer, questchain_id integer, quest_index integer);");

    return 0;
}

// checks if a sqlite table is empty
bool checkTable(std::string name) {
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name=" + toQString(name) + ";");
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