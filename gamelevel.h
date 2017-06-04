#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <QObject>

#include <maze.h>

class GAMELEVEL : public QObject
{
    Q_OBJECT
public:

    enum lvl
    {
        DFS,
        ELL
    };

    struct Level
    {
        lvl flag;
        union
        {
            DFSMaze   *DM;
            EllerMaze *EM;
        };
    };

    Level  level;
    QTimer *timer;
    QTimer *secDecr;
    QTimer *timeSecDecr;

private:

    int mazeHeight;
    int mazeWidth;
    int score = 1000;
    int timeForTimeout;
    int currentTime;

public:

    explicit GAMELEVEL(lvl choise, int h, int w, int timeOut, QObject *parent = 0);
    ~GAMELEVEL();

    int getScore();
    int getCurrentTime();

signals:

public slots:

        void TimeOut();
        void littleDecrease();
        void bigDecrease();
        void coinIncrease();
        void secDecrease();
};

#endif // GAMELEVEL_H
