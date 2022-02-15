#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

int addPlayer(std::string name);
int initDatabases();
int initTables();

bool checkTable(std::string name);

QString quotesql( const std::string& s );
QString quotesql( const int& s );

#endif