#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <QDebug>
#include <QEventLoop>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QScrollArea>
#include <QTabWidget>
#include <QWidget>

#include "player.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        int currentWindow;

        MainWindow();
    
        std::string registerPlayer();

        void clearWindow();
        void playerProfile(Player player);
        void updateGUI(Player player);
};

#endif