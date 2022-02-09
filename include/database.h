#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

int addPlayer(std::string name);
int initDatabases();

#endif