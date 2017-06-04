#include "statistic.h"
#include "ui_Statistic.h"

#include <QTableWidgetItem>
#include <QString>
#include <string.h>

Statistic::Statistic(DEQUE<Player> *allPlayers,
                     MediaController *_mediaController,
                     QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistic)
{
    ui->setupUi(this);

    mediaController = _mediaController;

    this->resize(1000, 600);
    this->setFixedSize(1000, 600);

    allplayers = allPlayers;
    connect(this, SIGNAL(CallToRecreate()), this, SLOT(CallToRecreateSlot()));
}

Statistic::~Statistic()
{
    delete ui;
}

void Statistic::on_backTomenu_clicked()
{
    mediaController->playButtonClickSound();
    emit backToMenu();
    this->close();
}

void Statistic::CallToRecreateSlot()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(allplayers->getSize() + 1);
    ui->tableWidget->setColumnCount(11);

    char names[10] = "Nicknames";
    QWidget     *labelWidget1 = new     QWidget();
    QLabel      *label1       = new      QLabel();
    QHBoxLayout *layoutLabel1 = new QHBoxLayout();

    label1->setText(QString(names));
    layoutLabel1->addWidget(label1);
    layoutLabel1->setAlignment(Qt::AlignCenter);
    layoutLabel1->setContentsMargins(0, 0, 0, 0);
    labelWidget1->setLayout(layoutLabel1);
    ui->tableWidget->setCellWidget(0, 0, labelWidget1);

    for(int i = 1; i < 11; i++)
    {
        char level[15] = "Level ";
        char numLev[10];
        QWidget     *labelWidget = new     QWidget();
        QLabel      *label       = new      QLabel();
        QHBoxLayout *layoutLabel = new QHBoxLayout();

        itoa(i, numLev, 10);
        int j;
        for(j = 0; numLev[j] != '\0'; j++)
        {
            level[6+j] = numLev[j];
        }
        level[6+j] = numLev[j];
        label->setText(QString(level));
        layoutLabel->addWidget(label);
        layoutLabel->setAlignment(Qt::AlignCenter);
        layoutLabel->setContentsMargins(0, 0, 0, 0);
        labelWidget->setLayout(layoutLabel);
        ui->tableWidget->setCellWidget(0, i, labelWidget);
    }

    allplayers->sort();

    int i = 1;

    for(DEQUE<Player>::iterator it = allplayers->begin(); it != allplayers->end(); ++it, ++i)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString((*it).getNick())));
        for(int j = 1; j < 11; j++)
        {
            char str[20];
            itoa((*it).getScoreOn(j-1), str, 10);
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString(str), i));
        }
    }
}
