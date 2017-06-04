#ifndef MAINMENU_H
#define MAINMENU_H

#include <windows.h>

#include <QMainWindow>
#include <QWidget>

#include <mediacontroller.h>
#include <deque.h>
#include <levels.h>
#include <statistic.h>
#include <player.h>

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(Player *currentPlayer,
                      DEQUE<Player>* allPlayers,
                      MediaController *_mediaController,
                      QWidget *parent = 0);
    ~MainMenu();

signals:

private slots:

    void on_goToPlayButton_clicked();

    void on_quitGame_clicked();

    void on_stat_clicked();

private:

    Ui::MainMenu   *ui;
    QGraphicsScene *scene;
    DFSMaze        *img;
    Levels         *levels;
    Statistic      *statistic;

    MediaController *mediaController;
};

#endif // MAINMENU_H
