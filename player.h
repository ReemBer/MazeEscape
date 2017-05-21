#ifndef PLAYER_H
#define PLAYER_H

#include <cstring>
#include <QMessageBox>
#include <QString>
#include <string>

using namespace std;

class Player
{
private:

    static const int LEVEL_COUNT = 10;
           const int MAXLEN      = 25;

private:

    int   nickSize;
    char *nick;
    int  *lvlScore;

public:

    Player();
    Player(char* Nick);
    Player(char* Nick, int* LvlScore);
    Player(const Player& another);
    ~Player();

    char* getNick();
    void  setNick(char* newNick);

    int  getScoreOn(int            level);
    void setScoreOn(int level, int score);

    friend bool operator ==(Player& first, Player& second);
    friend bool operator !=(Player& first, Player& second);
    friend bool operator  >(Player& first, Player& second);
    friend bool operator  <(Player& first, Player& second);

    Player& operator =(Player& another);

};

#endif // PLAYER_H
