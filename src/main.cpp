#include <iostream>
#include <QApplication>
#include <QFile>
#include <QLabel>
#include <QSqlQuery>
#include <QTextEdit>
#include <QWidget>
#include <string>

#include "database.h"
#include "gui.h"
#include "player.h"
#include "quest.h"
#include "version.h"

int main(int argc, char *argv[]) {
    // testVersion();
    
    QApplication app(argc, argv);

    // Load style
    QFile styleFile( "../style.qss" );
    styleFile.open( QFile::ReadOnly );
    QString style( styleFile.readAll() );
    app.setStyleSheet( style );

    initDatabases();

    bool playerExists = checkTable("player"); // only allow a single entry in player table
    // std::cout << exists << "\n";

    initTables();

    MainWindow mainwindow;

    std::string title = "test questchain";
    std::string description = "this is a test questchain";
    QuestChain questChain;
    // QuestChain questChain(title, description);

    Player player;

    if (playerExists == false) {
        std::string name = mainwindow.registerPlayer();
        player = Player(name);
    }
    else {
        player = Player(1); // get first entry in database
    }

    std::cout << "Player name: " << player.name << "\n";

    mainwindow.playerProfile(player);
    player.levelUp();
    mainwindow.updateGUI(player);

    return app.exec();
}