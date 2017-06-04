#include "mazeescape.h"

MazeEscape::MazeEscape(QObject *parent) : QObject(parent)
{
    try
    {
        currentPlayer  = nullptr;
        mainMenuWindow = nullptr;
        loginWindow    = nullptr;

        ifstream users(userFileName);
        char curNickName[20];
        while(!users.eof())
        {
           users >> curNickName;
           if(users.eof()) break;
           Player curPlayer(curNickName);

           for(int j = 0; j < LEVEL_COUNT; j++)
           {
               int curlvlscore;
               users >> curlvlscore;
               curPlayer.setScoreOn(j, curlvlscore);
           }
           allPlayers.push_back(curPlayer);

        }
        users.close();

        mediaController = new MediaController(this);

        loginWindow = new Login(&allPlayers, mediaController);

        connect(loginWindow, &Login::loggedIn, mediaController, &MediaController::playMainThemeSound);
        connect(loginWindow, SIGNAL(loggedIn()), this, SLOT(loginCompleted()));
    }
    catch(...)
    {
        cout << "AAAAAAAAAAAAAAAAA\n";
    }
}

MazeEscape::~MazeEscape()
{
    ofstream players(userFileName);
    DEQUE<Player>::iterator it = allPlayers.begin();


    while(it != allPlayers.end())
    {
        players << (*it).getNick() << endl;
//        players << (*it).getPassword() << endl;
//        players << (*it).getEmail() << endl;
        for(int i = 0; i < LEVEL_COUNT; i++)
        {
            players << (*it).getScoreOn(i) << ' ';
        }
        ++it;
        if(it != allPlayers.end()) players << endl;
    }
    players.close();
    if(mainMenuWindow) delete mainMenuWindow;
    if(loginWindow)    delete loginWindow;
    if(currentPlayer)  delete currentPlayer;
}

void MazeEscape::startGame()
{
    loginWindow->show();
}

void MazeEscape::loginCompleted()
{
    char* tmp = loginWindow->getNickName();
    currentPlayer = new Player(tmp);

    bool exst = false;
    DEQUE<Player>::iterator it;
    for(it = allPlayers.begin(); it != allPlayers.end(); ++it)
    {
        if(!strcmp((*it).getNick(), currentPlayer->getNick()))
        {
            exst = true;
            break;
        }
    }
    if(exst)
    {
        currentPlayer = &(*it);
    }
    else
    {
        for(int i = 0; i < LEVEL_COUNT; i++)
        {
            currentPlayer->setScoreOn(i, 0);
        }
        allPlayers.push_back(*currentPlayer);
        for(it = allPlayers.begin(); it != allPlayers.end(); ++it)
        {
            if(!strcmp((*it).getNick(), currentPlayer->getNick()))
            {
                currentPlayer = &(*it);
                break;
            }
        }
    }
    try
    {
        mainMenuWindow = new MainMenu(currentPlayer, &allPlayers, mediaController);
        if(!mainMenuWindow) throw 1;
        mainMenuWindow->show();
    }
    catch(int ex)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("Error in constructor MainMenu: NOT ENOUGHT MEMORY for main window");
        m->exec();
        terminate();
    }
}
