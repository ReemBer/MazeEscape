#ifndef PLAY_WINDOW_H
#define PLAY_WINDOW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include "maze.h"

namespace Ui {
class Play_window;
}

class Play_window : public QWidget
{
    Q_OBJECT

public:
    explicit Play_window(QWidget *parent = 0);
    ~Play_window();

private slots:
    void on_checkBox_clicked();

private:

    Ui::Play_window *ui;
    QGraphicsScene *scene;
    BFS_and_DFS_Maze *m;
};

#endif // PLAY_WINDOW_H
