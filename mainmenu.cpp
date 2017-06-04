#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(Player *currentPlayer,
                   DEQUE<Player> *allPlayers,
                   MediaController *_mediaController,
                   QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    mediaController = _mediaController;

    this->resize(1000, 600);
    this->setFixedSize(1000, 600);
    try
    {
        scene     = new QGraphicsScene();
        img       = new DFSMaze(8, 20);
        levels    = new Levels(currentPlayer, allPlayers, mediaController);
        statistic = new Statistic(allPlayers, mediaController);
        if(!scene || !img || !levels || !statistic) throw 1;
        ui->graphicsView->setScene(scene);
        scene->addItem(img);

        connect(levels, &Levels::backToMenu, this, &MainMenu::show);
        connect(statistic, &Statistic::backToMenu, this, &MainMenu::show);
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in constructor MainMenu: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

MainMenu::~MainMenu()
{

    delete ui;
}

void MainMenu::on_goToPlayButton_clicked()
{
    mediaController->playButtonClickSound();
    levels->show();
    this->close();
}

void MainMenu::on_quitGame_clicked()
{
    mediaController->playButtonClickSound();
    Sleep(DWORD(375));
    this->close();
}

void MainMenu::on_stat_clicked()
{
    mediaController->playButtonClickSound();
    emit statistic->CallToRecreate();
    statistic->show();
    this->close();
}
