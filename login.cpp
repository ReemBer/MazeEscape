#include "login.h"
#include "ui_login.h"

Login::Login(DEQUE<Player> *allPlayers, MediaController *_mediaController, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    allplayers = allPlayers;
    mediaController = _mediaController;

    ui->OK->setEnabled(false);
    QRegExp exp("[a-zA-Z0-9]{1,20}");
    ui->nickNameLine->setValidator(new QRegExpValidator(exp, this));
    ui->password->setValidator(new QRegExpValidator(exp, this));
    ui->password->setEchoMode(QLineEdit::EchoMode::Password);

    connect(ui->nickNameLine, SIGNAL(textChanged(QString)), this, SLOT(OkEnabled()));
    connect(ui->password, SIGNAL(textChanged(QString)), this, SLOT(OkEnabled()));
}

Login::~Login()
{
    allplayers = nullptr;
    delete ui;
}

void Login::OkEnabled()
{
    ui->OK->setEnabled(ui->nickNameLine->hasAcceptableInput());
}

void Login::on_OK_clicked()
{
    mediaController->playButtonClickSound();
    try
    {
        QString curNickName = ui->nickNameLine->displayText();
        nickNameSize = curNickName.size();
        nickName = new char[nickNameSize+1];
        if(!nickName) throw 1;
        const char* tmp = curNickName.toStdString().c_str();
        for(int i = 0; i < nickNameSize+1; i++)
        {
            nickName[i] = tmp[i];
        }
        emit loggedIn();
        this->close();
    }
    catch(int i)
    {
       QMessageBox *m = new QMessageBox();
       m->setText("Error in slot Login::on_OK_clicked: NOT ENOUGHT MEMORY");
       m->exec();
       terminate();
    }

}

char* Login::getNickName()
{
    return nickName;
}

int Login::getNickNameSize()
{
    return nickNameSize;
}

void Login::on_signUp_clicked()
{
    mediaController->playButtonClickSound();
    Sleep(DWORD(375));
    this->close();
}
