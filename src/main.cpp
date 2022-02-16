#include <iostream>
#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QIODevice>
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

std::vector<QuestChain> questChains;
std::vector<Quest> quests;

int main(int argc, char *argv[]) {
    // testVersion();
        
    QApplication app(argc, argv);

    std::cout << "loading fonts" << "\n";
    QFontDatabase fontdb;
    int fontId = QFontDatabase::addApplicationFont("/Users/Sinon/Dev/LifequestDesktop/fonts/BebasNeue.otf");
    // std::cout << fontId << "\n";
    std::cout << "finished loading fonts" << "\n";

    // Load style
    QFile styleFile( "/Users/Sinon/Dev/LifequestDesktop/style.qss" );
    styleFile.open( QIODevice::ReadOnly | QIODevice::Text );
    QString style( styleFile.readAll() );
    styleFile.close();
    app.setStyleSheet( style );

    initDatabases();

    bool playerExists = checkTable("player"); // only allow a single entry in player table
    // std::cout << exists << "\n";

    initTables();

    // create objects from databases
    std::cout << "creating objects from databases" << "\n";
    questChains = createQuestChains();
    quests = createQuests();
    std::cout << "finished creating objects from databases" << "\n";

    MainWindow mainwindow;

    // std::string title = "test questchain";
    // std::string description = "this is a test questchain";
    // QuestChain questChain(title, description);

    // int questChainIndex = 1;
    // std::string questTitle = "test quest";
    // std::string questDescription = "this is a test quest.";
    // Quest quest(questChain, questChainIndex, questTitle, questDescription);

    Player player;

    if (playerExists == false) {
        std::string name = mainwindow.registerPlayer();
        player = Player(name);
    }
    else {
        player = Player(1); // get first entry in database (replace with login system)
    }

    std::cout << "Player name: " << player.name << "\n";

    mainwindow.playerProfile(player);
    // player.levelUp();
    QuestChain questChain = questChains.at(0);
    player.acceptQuestChain(questChain);
    mainwindow.updateGUI(player);

    return app.exec();
}