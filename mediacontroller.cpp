#include "mediacontroller.h"

MediaController::MediaController(QObject *parent) : QObject(parent)
{
    mainTheme   = new QMediaPlayer(this);
    buttonClick = new QMediaPlayer(this);
    keyTap      = new QMediaPlayer(this);
    warning     = new QMediaPlayer(this);
    coinTake    = new QMediaPlayer(this);

    keyTapPlaylist      = new QMediaPlaylist(keyTap);
    warningPlaylist     = new QMediaPlaylist(warning);
    coinTakePlayList    = new QMediaPlaylist(coinTake);
    mainThemePlaylist   = new QMediaPlaylist(mainTheme);
    buttonClickPlaylist = new QMediaPlaylist(buttonClick);

    //Adding sounds
    mainThemePlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    mainTheme->setPlaylist(mainThemePlaylist);
    mainTheme->setVolume(50);
    mainThemePlaylist->addMedia(QUrl(QString("sounds/mainTheme.mp3")));

    buttonClick->setPlaylist(buttonClickPlaylist);
    buttonClickPlaylist->addMedia(QUrl(QString("sounds/button2.wav")));

    warning->setPlaylist(warningPlaylist);
    warning->setVolume(50);
    warningPlaylist->addMedia(QUrl(QString("sounds/warning.wav")));

    coinTake->setPlaylist(coinTakePlayList);
    coinTakePlayList->addMedia(QUrl(QString("sounds/coin.wav")));
}

void MediaController::setMainThemePlayerParrent(QObject *parent) {
    if (parent) {
       mainTheme->setParent(parent);
    }
}

void MediaController::setButtonClickPlayerParrent(QObject *parent) {
    if (parent) {
        buttonClick->setParent(parent);
    }
}

void MediaController::setKeyBoardTapPlayerParrent(QObject *parent) {
    if (parent) {
        keyTap->setParent(parent);
    }
}

void MediaController::playButtonClickSound() {
    buttonClick->play();
}

void MediaController::playKeyBoardTapSound() {
    keyTap->play();
}

void MediaController::playMainThemeSound() {
    mainTheme->play();
}

void MediaController::playWarning() {
    warning->play();
}

void MediaController::playCoinTake() {
    coinTake->play();
}
