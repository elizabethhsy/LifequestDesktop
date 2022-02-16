#include "gui.h"

MainWindow::MainWindow() {
    this->resize(500, 500);
    this->setObjectName("mainWindow");

    QWidget *centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);
    centralWidget->setObjectName("centralWidget");
    
    this->show();
}

void MainWindow::clearWindow() {
    QWidget *centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);
}

void MainWindow::playerProfile(Player player) {
    clearWindow();
    currentWindow = 1;

    QWidget *centralWidget = this->centralWidget();
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *playerName = new QLabel(this);
    playerName->setText(QString::fromStdString(player.name));
    playerName->setObjectName("title");

    QLabel *level = new QLabel(this);
    level->setText("Level " + QString::number(player.level) + " (" + QString::number(player.experience) + "XP)");
    level->setObjectName("subtitle");

    QLabel *strength = new QLabel(this);
    strength->setText("Strength: " + QString::number(player.strength));
    strength->setObjectName("stat");

    QLabel *agility = new QLabel(this);
    agility->setText("Agility: " + QString::number(player.agility));
    agility->setObjectName("stat");

    QLabel *vitality = new QLabel(this);
    vitality->setText("Vitality: " + QString::number(player.vitality));
    vitality->setObjectName("stat");

    QLabel *intelligence = new QLabel(this);
    intelligence->setText("Intelligence: " + QString::number(player.intelligence));
    intelligence->setObjectName("stat");

    QLabel *wisdom = new QLabel(this);
    wisdom->setText("Wisdom: " + QString::number(player.wisdom));
    wisdom->setObjectName("stat");

    QLabel *willpower = new QLabel(this);
    willpower->setText("Willpower: " + QString::number(player.willpower));
    willpower->setObjectName("stat");

    QLabel *fame = new QLabel(this);
    fame->setText("Fame: " + QString::number(player.fame));
    fame->setObjectName("stat");

    // subtabs
    QTabWidget *playerTabs = new QTabWidget(this);

    // quest subtab
    QScrollArea *questScroll = new QScrollArea(this);
    QWidget *questTab = new QWidget(this);
    QVBoxLayout *questLayout = new QVBoxLayout(questTab);

    // QLabel *questLabel = new QLabel(this);
    // questLabel->setText("Quest Label");
    // questLayout->addWidget(questLabel);

    QSqlQuery query;
    query.exec("SELECT * from accept_questchain WHERE player_id = " + toQString(player.id));
    while (query.next()) {
        int questChainId = query.value(2).toInt();
        int currentQuestIndex = query.value(3).toInt();
        // std::cout << "quest chain id: " << questChainId << "\n";

        QuestChain questChain = questChains.at(questChainId-1);

        QLabel *questTitle = new QLabel(this);
        Quest currentQuest = quests.at(questChain.childQuests.at(currentQuestIndex-1)-1);
        // std::cout << "current quest title: " << currentQuest.title << "\n";
        std::string title = questChain.title + ": " + currentQuest.title + " [" + std::to_string(currentQuest.questChainIndex) + "/" + std::to_string(questChain.childQuests.size()) + "]";
        QString questChainTitle = toTrimmedQString(title);
        questTitle->setText(questChainTitle);
        questTitle->setObjectName("header");
        
        QLabel *questDescription = new QLabel(this);
        questDescription->setText(toTrimmedQString(currentQuest.description));

        questLayout->addWidget(questTitle);
        questLayout->addWidget(questDescription);

        questLayout->addStretch();
    }

    // skills subtab
    QScrollArea *skillScroll = new QScrollArea(this);
    QWidget *skillTab = new QWidget(this);
    QVBoxLayout *skillLayout = new QVBoxLayout(skillTab);

    // QLabel *skillLabel = new QLabel(this);
    // skillLabel->setText("Skill Label");
    // skillLayout->addWidget(skillLabel);

    skillLayout->addStretch();

    questScroll->setWidget(questTab);
    skillScroll->setWidget(skillTab);
    playerTabs->addTab(questScroll, "Quest");
    playerTabs->addTab(skillScroll, "Skills");

    // add the widgets to the window
    layout->addWidget(playerName);
    layout->addWidget(level);
    layout->addWidget(strength);
    layout->addWidget(agility);
    layout->addWidget(vitality);
    layout->addWidget(intelligence);
    layout->addWidget(wisdom);
    layout->addWidget(willpower);
    if (player.fame != 0) {
        std::cout << player.fame << "\n";
        layout->addWidget(fame); // only display if stat is unlocked
    }

    layout->addWidget(playerTabs);
    layout->addStretch();
    this->show();
}

std::string MainWindow::registerPlayer() {
    clearWindow();
    currentWindow = 0;

    std::string name = "";

    QWidget *centralWidget = this->centralWidget();
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *label = new QLabel(this);
    label->setText("Register Player");
    label->setObjectName("title");

    QLineEdit *inputBox = new QLineEdit(this);

    QPushButton *button = new QPushButton("&Register", this);

    layout->addWidget(label);
    layout->addWidget(inputBox);
    layout->addWidget(button);
    layout->addStretch();
    this->show();

    QEventLoop loop;
    QObject::connect(inputBox, &QLineEdit::returnPressed, &loop, &QEventLoop::quit);
    QObject::connect(button, &QPushButton::clicked, &loop, &QEventLoop::quit);
    QObject::connect(inputBox, &QLineEdit::returnPressed, [&name, inputBox](){
        name = inputBox->text().toStdString();
    });
    QObject::connect(button, &QPushButton::clicked, [&name, inputBox]() {
        name = inputBox->text().toStdString();
    });
    loop.exec();

    return name;
}

void MainWindow::updateGUI(Player player) {
    if (currentWindow == 0) {
        registerPlayer();
    }
    else if (currentWindow == 1) {
        playerProfile(player);
    }
}