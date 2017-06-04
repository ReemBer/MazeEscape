#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class MediaController : public QObject
{
    Q_OBJECT
public:
    explicit MediaController(QObject *parent = 0);

    void setButtonClickPlayerParrent(QObject *parent);
    void setKeyBoardTapPlayerParrent(QObject *parent);
    void setMainThemePlayerParrent(QObject *parent);

signals:

public slots:

    void playButtonClickSound();
    void playKeyBoardTapSound();
    void playMainThemeSound();
    void playWarning();
    void playCoinTake();

    void stopButtonClickSound(){}
    void stopKeyBoardTapSound(){}
    void stopMainThemeSound(){}
    void stopWarning(){}

    void pauseButtonClickSound(){}
    void pauseKeyBoardTapSound(){}
    void pauseMainThemeSound(){}
    void pauseWarning(){}

private:

    QMediaPlayer *mainTheme;
    QMediaPlayer *buttonClick;
    QMediaPlayer *keyTap;
    QMediaPlayer *warning;
    QMediaPlayer *coinTake;

    QMediaPlaylist *mainThemePlaylist;
    QMediaPlaylist *buttonClickPlaylist;
    QMediaPlaylist *keyTapPlaylist;
    QMediaPlaylist *warningPlaylist;
    QMediaPlaylist *coinTakePlayList;
};

#endif // MEDIACONTROLLER_H
