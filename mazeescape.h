#ifndef MAZEESCAPE_H
#define MAZEESCAPE_H

#include <QObject>
#include <QString>

#include <fstream>
#include <gamelevel.h>
#include <deque.h>
#include <player.h>
#include <mainmenu.h>
#include <levels.h>
#include <login.h>
#include "mediacontroller.h"

using namespace std;

/**
 * @brief The MazeEscapeGame class
 * Данный класс содержит основную информацию об игре.
 * В нём содержатся :
 * - Массив уровней:
 * - статические уровни [10 шт];
 * - список зарегистрированных игроков [подгружается из файла users.txt];
 */
class MazeEscape : public QObject
{
    friend class Top10;
    Q_OBJECT

public:

    const int DFS_LEVEL_COUNT = 5;
    const int ELL_LEVEL_COUNT = 5;
    const int LEVEL_COUNT     = DFS_LEVEL_COUNT + ELL_LEVEL_COUNT;

    const char* userFileName  = "players.txt";



private:

    Player       *currentPlayer;
    DEQUE<Player> allPlayers;

    MediaController *mediaController;

public:

    MainMenu *mainMenuWindow;
    Login    *loginWindow;

public:

    explicit MazeEscape(QObject *parent = 0);
    ~MazeEscape();

    void startGame();

signals:

public slots:

    void loginCompleted();
};

#endif // MAZEESCAPE_H
