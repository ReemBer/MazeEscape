#include "playwindow.h"
#include "ui_playwindow.h"
#include <windows.h>

PlayWindow::PlayWindow(Player *currentPlayer,
                       int currentLevel,
                       GAMELEVEL::lvl choice,
                       int h, int w, int timeOut,
                       MediaController *_mediaController,
                       QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);

    mediaController = _mediaController;
    fullTime = timeOut;

    this->resize(1000, 600);
    this->setFixedSize(1000, 600);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedWidth(900);

    warningTimer = new QTimer(this);
    timer = new QTimer(this);
    m = new GAMELEVEL(choice, h, w, timeOut);
    currentplayer = currentPlayer;
    currentlevel  = currentLevel;
    switch(m->level.flag)
    {
    case GAMELEVEL::DFS:
    {
        scene->addItem(m->level.DM);
        break;
    }
    case GAMELEVEL::ELL:
    {
        scene->addItem(m->level.EM);
        break;
    }
    }
    char tmp[10];
    ui->TimerLabel->setText(itoa(m->getCurrentTime(), tmp, 10));
    ui->ScoreLabel->setText(itoa(m->getScore(), tmp, 10));
    connect(timer, &QTimer::timeout, this, &PlayWindow::check_state);
    connect(warningTimer, &QTimer::timeout, this, &PlayWindow::checkWarning);
    timer->start(1000/25);
    warningTimer->start(200);
}

PlayWindow::~PlayWindow()
{
    delete ui;
}

void PlayWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void PlayWindow::check_state()
{
    char tmp[10];
    ui->TimerLabel->setText(itoa(m->getCurrentTime(), tmp, 10));
    ui->ScoreLabel->setText(itoa(m->getScore(), tmp, 10));
    int dx = 0, dy = 0; // Приращения координат

    // Считывание состояний клавиш
    if(GetAsyncKeyState('A'))
    {
        dx = 0 , dy = -1;
    }
    else if(GetAsyncKeyState('D'))
    {
        dx = 0 , dy = 1;
    }
    else if(GetAsyncKeyState('W'))
    {
        dx = -1 , dy = 0;
    }
    else if(GetAsyncKeyState('S'))
    {
        dx = 1 , dy = 0;
    }

    int state;
    switch(m->level.flag)
    {
        case GAMELEVEL::DFS:
        {
            state = m->level.DM->character_move(dx, dy);
            break;
        }
        case GAMELEVEL::ELL:
        {
            state = m->level.EM->character_move(dx, dy);
            break;
        }
    }

    if((state%10)) gameOverSlot();
    if(state/10) {
        mediaController->playCoinTake();
        m->coinIncrease();
    }
    else
    {
        ui->graphicsView->scene()->update();
        repaint();
    }
}

void PlayWindow::checkWarning() {
    if((double)m->getCurrentTime() <= max(0.2*((double)fullTime), 3.)) {
        mediaController->playWarning();
    }
}

void PlayWindow::on_help_show_clicked(bool checked)
{
    if(checked)
    {
        m->secDecr->start(50);
    }
    else
    {
        m->secDecr->start(1000);
    }
    switch(m->level.flag)
    {
        case GAMELEVEL::DFS:
        {
            m->level.DM->set_way_visible(checked);
            break;
        }
        case GAMELEVEL::ELL:
        {
            m->level.EM->set_way_visible(checked);
        }
    }

    ui->graphicsView->scene()->update();
    repaint();
}

void PlayWindow::on_pushButton_clicked()
{
    mediaController->playButtonClickSound();
    timer->stop();
    warningTimer->stop();
    emit backToLevels();
    this->close();
}

void PlayWindow::gameOverSlot()
{
    totalScore = m->getScore();
    currentplayer->setScoreOn(currentlevel, max(totalScore, currentplayer->getScoreOn(currentlevel)));
    timer->stop();
    warningTimer->stop();
    emit backToLevels();

    this->close();
}
