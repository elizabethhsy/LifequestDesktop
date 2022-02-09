#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QSqlQuery>
#include <QTextEdit>
#include <QWidget>
#include <string>

#include "database.h"
#include "gui.h"
#include "version.h"

int main(int argc, char *argv[]) {
    int width = 1000;
    int height = 600;

    testVersion();
    
    QApplication app(argc, argv);

    initDatabases();

    QWidget window;

    window.resize(width, height);
    window.setWindowTitle("Lifequest");

    QLabel label("label", &window);
    label.setGeometry(0.1*width, 0.1*height, 100, 100);

    window.show();

    return app.exec();
}
