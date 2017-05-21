#include "player.h"

Player::Player()
{
    try
    {
        nick = nullptr;
        nickSize = 0;
        lvlScore = new int[LEVEL_COUNT];
        if(!lvlScore) throw 1;
        for(int j = 0; j < LEVEL_COUNT; j++)
        {
            lvlScore[j] = 0;
        }
    }
    catch(int i)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor MainMenu: NOT ENOUGHT MEMORY for main window");
        m->exec();
    }
}

Player::Player(char *Nick)
{
    try
    {
        int len = 0;
        for(; Nick[len] != '\0' && Nick[len] != '\n' && len != MAXLEN; len++);
        nick = new char[len+1];
        if(!nick) throw 'e';
        nickSize = len;
        for(int i = 0; i < len; i++)
        {
            nick[i] = Nick[i];
        }
        nick[len] = '\0';

        lvlScore = new int[LEVEL_COUNT];
        if(!lvlScore) throw 1;
        for(int j = 0; j < LEVEL_COUNT; j++)
        {
            lvlScore[j] = 0;
        }
    }
    catch(char ex)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor Player::Player : NOT ENOUGHT MEMORY for nick");
        m->exec();
    }
    catch(int i)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor Player::Player : NOT ENOUGHT MEMORY for lvlScore");
        m->exec();
    }
}

Player::Player(char *Nick, int *LvlScore)
{
    try
    {
        int len = 0;
        for(; Nick[len] != '\0' && len != MAXLEN; len++);
        nick = new char[len+1];
        if(!nick) throw 'e';
        nickSize = len;
        for(int i = 0; i < len; i++)
        {
            nick[i] = Nick[i];
        }
        nick[len] = '\0';

        lvlScore = new int[LEVEL_COUNT];
        if(!lvlScore) throw 1;
        for(int i = 0; i < LEVEL_COUNT; i++)
        {
            lvlScore[i] = LvlScore[i];
        }
    }
    catch(char ex)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor Player::Player : NOT ENOUGHT MEMORY for nick");
        m->exec();
    }
    catch(int i)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor Player::Player : NOT ENOUGHT MEMORY for lvlScore");
        m->exec();
    }
}

Player::Player(const Player &another)
{
    try
    {
        nickSize = another.nickSize;
        nick = new char[nickSize+1];
        if(!nick) throw 'e';
        lvlScore = new int[LEVEL_COUNT];
        if(!lvlScore) throw 1;
        for(int i = 0; i < nickSize+1; i++)
        {
            nick[i] = another.nick[i];
        }
        for(int i = 0; i < LEVEL_COUNT; i++)
        {
            lvlScore[i] = another.lvlScore[i];
        }
    }
    catch(char ex)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor Player::Player : NOT ENOUGHT MEMORY for nick");
        m->exec();

    }
    catch(int ex)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor Player::Player : NOT ENOUGHT MEMORY for lvlScore");
        m->exec();
    }
}

Player::~Player()
{
    delete[]     nick;
    delete[] lvlScore;
}

char* Player::getNick()
{
    return nick;
}

void Player::setNick(char *newNick)
{
    try
    {
        int newSize;
        for(newSize = 0; newNick[newSize] !='\0'; newSize++);
        nickSize = newSize;
        if(nick) delete[] nick;
        nick = new char[newSize+1];
        if(!nick) throw 'e';
        for(int i = 0; i < newSize+1; i++)
        {
            nick[i] = newNick[i];
        }
    }
    catch(char ex)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor Player::Player : NOT ENOUGHT MEMORY for nick");
        m->exec();
    }
}

int Player::getScoreOn(int level)
{
    try
    {
        if(level > LEVEL_COUNT) throw 1;
        if(level < 0) throw 1.0;
        return lvlScore[level];
    }
    catch(int ex)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor Player::Player : NOT ENOUGHT MEMORY for nick");
        m->exec();
    }
    catch(double i)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor Player::Player : NOT ENOUGHT MEMORY for lvlScore");
        m->exec();
    }
}

void Player::setScoreOn(int level, int score)
{
    lvlScore[level] = score;
}

Player& Player::operator=(Player& another)
{
    try
    {
        if(nick) delete[] nick;
        nickSize = another.nickSize;
        nick = new char[nickSize+1];
        if(!nick) throw 'e';
        for(int i = 0; i < nickSize; i++)
        {
            nick[i] = another.nick[i];
        }
        nick[nickSize] = '\0';

        for(int i = 0; i < LEVEL_COUNT; i++)
        {
            lvlScore[i] = another.lvlScore[i];
        }
    }
    catch(char ex)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor Player::Player : NOT ENOUGHT MEMORY for nick");
        m->exec();
    }
}

bool operator == (Player& first, Player& second)
{
    int firstCnt = 0;
    int secondCnt = 0;
    for(int i = 0; i < Player::LEVEL_COUNT; i++)
    {
        firstCnt  += first.lvlScore[i];
        secondCnt += second.lvlScore[i];
    }

    if(firstCnt == secondCnt)
    {
        return true;
    }
    else
    {
        if(!strcmp(first.nick, second.nick))
        {
            return true;
        }
        else return false;
    }
}

bool operator != (Player& first, Player& second)
{
    int firstCnt = 0;
    int secondCnt = 0;
    for(int i = 0; i < Player::LEVEL_COUNT; i++)
    {
        firstCnt  += first.lvlScore[i];
        secondCnt += second.lvlScore[i];
    }

    if(firstCnt != secondCnt)
    {
        return true;
    }
    else
    {
        if(strcmp(first.nick, second.nick))
        {
            return true;
        }
        else return false;
    }
}

bool operator >(Player& first, Player& second)
{
    int firstCnt = 0;
    int secondCnt = 0;
    for(int i = 0; i < Player::LEVEL_COUNT; i++)
    {
        firstCnt  += first.lvlScore[i];
        secondCnt += second.lvlScore[i];
    }

    if(firstCnt > secondCnt)
    {
        return true;
    }
    else return false;
}

bool operator <(Player& first, Player& second)
{
    int firstCnt = 0;
    int secondCnt = 0;
    for(int i = 0; i < Player::LEVEL_COUNT; i++)
    {
        firstCnt  += first.lvlScore[i];
        secondCnt += second.lvlScore[i];
    }

    if(firstCnt < secondCnt)
    {
        return true;
    }
    else
    {
        if(strcmp(first.nick, second.nick) < 0)
        {
            return true;
        }
        else return false;
    }
}
