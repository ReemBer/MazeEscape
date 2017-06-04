#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QWidget>
#include <QGraphicsScene>

#include <mediacontroller.h>
#include <gamelevel.h>
#include <player.h>


namespace Ui {
class PlayWindow;
}

class PlayWindow : public QWidget
{
    Q_OBJECT

    QTimer *timer;
    QTimer *warningTimer;

public:
    explicit PlayWindow(Player *currentPlayer,
                        int currentLevel,
                        GAMELEVEL::lvl choice,
                        int h, int w, int timeOut,
                        MediaController *_mediaController,
                        QWidget *parent = 0);
    ~PlayWindow();

signals:

    void backToLevels();

protected:

    void paintEvent(QPaintEvent *event);

private slots:

    void check_state();

    void checkWarning();

    void on_help_show_clicked(bool checked);

    void on_pushButton_clicked();

    void gameOverSlot();

private:

    Ui::PlayWindow *ui;
    QGraphicsScene *scene;
    int             fullTime;
    int             totalScore;
    int             currentlevel;
    Player         *currentplayer;
    GAMELEVEL      *m;

    MediaController *mediaController;
};

#endif // PLAYWINDOW_H
