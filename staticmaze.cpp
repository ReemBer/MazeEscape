#include <maze.h>

void StaticMaze::createMazePattern(int h, int w, bool f) // "Заготовка лабиринта"
{
    CELLSIZE = min(820/w, 520/h);
    height = h;
    width = w;
    maze = new Cell*[height];
    for(int i = 0; i < height; i++)
    {
        maze[i] = new Cell[width];

        if(f)
        {
            for(int j = 0; j < width; j++)
            {
                if(!(i%2))
                {
                    maze[i][j] = WALL;
                }
                else if( !(j%2) )
                {
                    maze[i][j] = WALL;
                }
                else
                {
                    maze[i][j] = EMPTY;
                }
            }
        }
        else
        {
            for(int j = 0; j < width; j++)
            {
                maze[i][j] = EMPTY;
            }
        }
    }
}

StaticMaze::StaticMaze(bool f) : Maze() // Создание "заготовки лабиринта" по-умолчанию
{
    USE_HELP = false;
    createMazePattern(HEIGHT, WIDTH, f);
}

StaticMaze::StaticMaze(int h, int w, bool f) : Maze() // Создание "Заготовки лабиринта" по размерам
{
    USE_HELP = false;
    createMazePattern(h, w, f);
}

void StaticMaze::set_way_visible(bool state)
{
    USE_HELP = state;
}

StaticMaze::~StaticMaze()
{
    clearUsed();
}

void StaticMaze::setUsed(int h, int w) // создание матрицы used
{
    clearUsed(); // отчисчаем "старый" массив used
    used_h = h;
    used_w = w;
    used = new bool*[h];
    for(int i = 0; i < h; i++)
    {
        used[i] = new bool[w];
        for(int j = 0; j < w; j++)
        {
            used[i][j] = false;
        }
    }
}

void StaticMaze::clearUsed() // Чистим массив used
{
    for(int i = used_h - 1; i >= 0; i--)
    {
        delete []used[i];
    }
    used_h = used_w = 0;
    delete used;
}

void StaticMaze::set_coins(unsigned int count) // Устанавливаем количество count бонусов в лабиринте
{
    unsigned int real_count = min(count, 10u); // берём "адекватное" количество бонусов

    while(real_count) // продолжаем, пока планируемое число бонусов не установлено
    {
        int x = 0;
        int y = 0;
        while(maze[x][y] != EMPTY) // Бонусы лежат только на свободных ячейках
        {
            x = rand()%(height-1) + 1;
            y = rand()%(width-1) + 1;
        }
        maze[x][y] = COIN;
        real_count--;
    }
}
