#ifndef LEVELS_H
#define LEVELS_H

#include <QWidget>

#include <deque.h>
#include <player.h>
#include <gamelevel.h>
#include <gamelevel.h>
#include <playwindow.h>
#include <mediacontroller.h>

namespace Ui {
class Levels;
}

class Levels : public QWidget
{
    Q_OBJECT

private:

    int currentLevel;
    Player *currentplayer;
    MediaController *mediaController;

public:
    explicit Levels(Player *currentPlayer,
                    DEQUE<Player>* allPlayers,
                    MediaController *_mediaController,
                    QWidget *parent = 0);
    ~Levels();

    void paintEvent(QPaintEvent *event);
signals:

    void backToMenu();

private slots:

    void on_back_clicked();

    void levelCompleted();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::Levels *ui;
    PlayWindow *playWindow;
};

#endif // LEVELS_H
