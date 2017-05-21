#ifndef TOP10_H
#define TOP10_H

#include <QWidget>
#include <deque.h>
#include <player.h>

namespace Ui {
class Statistic;
}

class Statistic : public QWidget
{
    Q_OBJECT

private:

    DEQUE<Player>* allplayers;

public:
    explicit Statistic(DEQUE<Player> *allPlayers, QWidget *parent = 0);
    ~Statistic();

signals:

    void CallToRecreate();

    void backToMenu();

private slots:

    void on_backTomenu_clicked();
    void CallToRecreateSlot();

private:
    Ui::Statistic *ui;
};

#endif // TOP10_H
