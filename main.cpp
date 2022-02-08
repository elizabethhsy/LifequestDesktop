#include <iostream>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QWidget>
#include "version.h"

int main(int argc, char *argv[]) {
    testVersion();
    
    QApplication app(argc, argv);

    QWidget window;

    window.resize(1000, 500);
    window.setWindowTitle("Lifequest");
    window.show();

    QString path = "path";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query;
    query.exec("create table person "
            "(id integer primary key, "
            "firstname varchar(20), "
            "lastname varchar(30), "
            "age integer)");

    return app.exec();
}
