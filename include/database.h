#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <vector>

int addPlayer(std::string name);
int initDatabases();
int initTables();

bool checkTable(std::string name);

QString toQString( const std::string& s );
QString toQString( const int& s );
QString toTrimmedQString (const std::string& s);
QString toTrimmedQString (const int& i);

#endif