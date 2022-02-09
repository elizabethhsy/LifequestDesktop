#include "database.h"

QString quotesql( const QString& s ) {
    return QString("'") + s + QString("'");
}

int addPlayer(std::string name) {
    QString qname = QString::fromStdString(name);
    QSqlQuery query;
    query.exec("INSERT INTO player (name, level) VALUES (" + quotesql(qname) + ", 1);");
    return 0;
}

int initDatabases() {
    QString path = "/Users/Sinon/Dev/LifequestDesktop/data.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query;
    query.exec("CREATE TABLE player "
            "(id integer primary key, "
            "name varchar(64), "
            "level integer);");

    return 0;
}