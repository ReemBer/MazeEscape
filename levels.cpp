#include "levels.h"
#include "ui_levels.h"

Levels::Levels(Player *currentPlayer, DEQUE<Player>* allPlayers, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Levels)
{
    ui->setupUi(this);

    this->resize(1000, 600);
    this->setFixedSize(1000, 600);

    playWindow    = nullptr;
    currentplayer = currentPlayer;
}

Levels::~Levels()
{
    delete playWindow;
    delete ui;
}

void Levels::on_back_clicked()
{
    emit backToMenu();
    this->close();
}

void Levels::on_pushButton_1_clicked()
{
    try
    {
        currentLevel = 0;
        if(playWindow) delete playWindow;
        playWindow = new PlayWindow(currentplayer, currentLevel, GAMELEVEL::DFS, 5, 10);
        if(!playWindow) throw 1;
        connect(playWindow, &PlayWindow::backToLevels, this, &Levels::show);
        playWindow->show();
        this->close();
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in slot on_pushbutton_clicked: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

void Levels::on_pushButton_2_clicked()
{
    try
    {
        currentLevel = 1;
        if(playWindow) delete playWindow;
        playWindow = new PlayWindow(currentplayer, currentLevel, GAMELEVEL::DFS, 7, 12);
        if(!playWindow) throw 1;
        connect(playWindow, &PlayWindow::backToLevels, this, &Levels::show);
        playWindow->show();
        this->close();
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in slot on_pushbutton_clicked: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

void Levels::on_pushButton_3_clicked()
{
    try
    {
        currentLevel = 2;
        if(playWindow) delete playWindow;
        playWindow = new PlayWindow(currentplayer, currentLevel, GAMELEVEL::DFS, 10, 15);
        if(!playWindow) throw 1;
        connect(playWindow, &PlayWindow::backToLevels, this, &Levels::show);
        playWindow->show();
        this->close();
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in slot on_pushbutton_clicked: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

void Levels::on_pushButton_4_clicked()
{
    try
    {
        currentLevel = 3;
        if(playWindow) delete playWindow;
        playWindow = new PlayWindow(currentplayer, currentLevel, GAMELEVEL::DFS, 12, 17);
        if(!playWindow) throw 1;
        connect(playWindow, &PlayWindow::backToLevels, this, &Levels::show);
        playWindow->show();
        this->close();
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in slot on_pushbutton_clicked: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

void Levels::on_pushButton_5_clicked()
{
    try
    {
        currentLevel = 4;
        if(playWindow) delete playWindow;
        playWindow = new PlayWindow(currentplayer, currentLevel, GAMELEVEL::DFS, 15, 20);
        if(!playWindow) throw 1;
        connect(playWindow, &PlayWindow::backToLevels, this, &Levels::show);
        playWindow->show();
        this->close();
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in slot on_pushbutton_clicked: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

void Levels::on_pushButton_6_clicked()
{
    try
    {
        currentLevel = 5;
        if(playWindow) delete playWindow;
        playWindow = new PlayWindow(currentplayer, currentLevel, GAMELEVEL::ELL, 5, 10);
        if(!playWindow) throw 1;
        connect(playWindow, &PlayWindow::backToLevels, this, &Levels::show);
        playWindow->show();
        this->close();
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in slot on_pushbutton_clicked: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

void Levels::on_pushButton_7_clicked()
{
    try
    {
        currentLevel = 6;
        if(playWindow) delete playWindow;
        playWindow = new PlayWindow(currentplayer, currentLevel, GAMELEVEL::ELL, 7, 12);
        if(!playWindow) throw 1;
        connect(playWindow, &PlayWindow::backToLevels, this, &Levels::show);
        playWindow->show();
        this->close();
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in slot on_pushbutton_clicked: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

void Levels::on_pushButton_8_clicked()
{
    try
    {
        currentLevel = 7;
        if(playWindow) delete playWindow;
        playWindow = new PlayWindow(currentplayer, currentLevel, GAMELEVEL::ELL, 10, 15);
        if(!playWindow) throw 1;
        connect(playWindow, &PlayWindow::backToLevels, this, &Levels::show);
        playWindow->show();
        this->close();
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in slot on_pushbutton_clicked: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

void Levels::on_pushButton_9_clicked()
{
    try
    {
        currentLevel = 8;
        if(playWindow) delete playWindow;
        playWindow = new PlayWindow(currentplayer, currentLevel, GAMELEVEL::ELL, 12, 17);
        if(!playWindow) throw 1;
        connect(playWindow, &PlayWindow::backToLevels, this, &Levels::show);
        playWindow->show();
        this->close();
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in slot on_pushbutton_clicked: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

void Levels::on_pushButton_10_clicked()
{
    try
    {
        currentLevel = 9;
        if(playWindow) delete playWindow;
        playWindow = new PlayWindow(currentplayer, currentLevel, GAMELEVEL::ELL, 15, 20);
        if(!playWindow) throw 1;
        connect(playWindow, &PlayWindow::backToLevels, this, &Levels::show);
        playWindow->show();
        this->close();
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in slot on_pushbutton_clicked: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }
}

void Levels::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawEllipse(180, 360, 150, 150);
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    painter.drawEllipse(450, 360, 150, 150);
    painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
    painter.drawEllipse(700, 360, 150, 150);
}
