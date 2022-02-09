#include <iostream>
#include <QApplication>
#include <QWidget>
#include <string>

#include "database.h"
#include "version.h"

int main(int argc, char *argv[]) {
    testVersion();
    
    QApplication app(argc, argv);

    QWidget window;

    window.resize(1000, 600);
    window.setWindowTitle("Lifequest");

    initDatabases();

    QSqlQuery query;
    
    addPlayer("Elizabeth");

    if (query.next()) {
        QString firstname = query.value(0).toString();
        qDebug() << "Firstname: " << firstname;
    }

    window.show();

    return app.exec();
}
