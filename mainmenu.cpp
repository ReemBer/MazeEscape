#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(Player *currentPlayer, DEQUE<Player> *allPlayers, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    this->resize(1000, 600);
    this->setFixedSize(1000, 600);
    try
    {
        scene     = new QGraphicsScene();
        img       = new DFSMaze(8, 20);
        levels    = new Levels(currentPlayer, allPlayers);
        statistic = new Statistic(allPlayers);
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
    levels->show();
    this->close();
}

void MainMenu::on_quitGame_clicked()
{
    this->close();
}

void MainMenu::on_stat_clicked()
{
    emit statistic->CallToRecreate();
    statistic->show();
    this->close();
}
