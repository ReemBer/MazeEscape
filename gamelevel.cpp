#include "gamelevel.h"

GAMELEVEL::GAMELEVEL(lvl choise, int h, int w, int timeOut, QObject *parent) : QObject(parent)
{
    try
    {
        mazeHeight = h;
        mazeWidth  = w;
        timeForTimeout = timeOut;
        currentTime    = timeOut;
        timer       = new QTimer();
        secDecr     = new QTimer();
        timeSecDecr = new QTimer();
        if(!timer || !secDecr) throw 1;
        connect(timer, &QTimer::timeout, this, &GAMELEVEL::TimeOut);
        connect(secDecr, &QTimer::timeout, this, &GAMELEVEL::littleDecrease);
        connect(timeSecDecr, &QTimer::timeout, this, &GAMELEVEL::secDecrease);
        timer->start(1000*timeOut);
        secDecr->start(1000);
        timeSecDecr->start(1000);
        switch(choise)
        {
            case DFS:
            {
                level.flag = DFS;
                level.DM  = new DFSMaze(h, w);
                if(!(level.DM)) throw 2;
                break;
            }
            case ELL:
            {
                level.flag = ELL;
                level.EM = new EllerMaze(h, w);
                if(!(level.EM)) throw 2;
                break;
            }
            default:
            {
                level.flag = DFS;
                level.DM  = new DFSMaze(h, w);
                if(!(level.DM)) throw 2;
                break;
            }
        }
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in constructor GAMELEVEL: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

GAMELEVEL::~GAMELEVEL()
{
    switch(level.flag)
    {
        case DFS:
        {
            delete level.DM;
            break;
        }
        default:
        {
            delete level.DM;
            break;
        }
    }
}

void GAMELEVEL::TimeOut()
{
    switch(level.flag)
    {
    case DFS:
    {
        level.DM->ReGen();
        break;
    }
    case ELL:
    {
        level.EM->ReGen();
        break;
    }
    }
    bigDecrease();
}

int GAMELEVEL::getScore()
{
    return score;
}

void GAMELEVEL::littleDecrease()
{
    score--;
}

void GAMELEVEL::bigDecrease()
{
    score -= 100;
    currentTime = timeForTimeout;
}

void GAMELEVEL::coinIncrease()
{
    score += 100;
}

int GAMELEVEL::getCurrentTime()
{
    return currentTime;
}

void GAMELEVEL::secDecrease()
{
    currentTime--;
}
