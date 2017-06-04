#ifndef LOGIN_H
#define LOGIN_H

#include <windows.h>

#include <QDialog>
#include <QString>
#include <QMessageBox>

#include <deque.h>
#include <player.h>
#include <mediacontroller.h>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT
private:

    DEQUE<Player> *allplayers;
    int   nickNameSize;
    char* nickName;
    MediaController *mediaController;

public:
    explicit Login(DEQUE<Player> *allPkayers, MediaController *_mediaController, QWidget *parent = 0);
    ~Login();

public:

    char* getNickName();
    int   getNickNameSize();

private:
    Ui::Login *ui;

signals:

    void loggedIn();

private slots:

    void OkEnabled();
    void on_OK_clicked();
    void on_signUp_clicked();
};

#endif // LOGIN_H
