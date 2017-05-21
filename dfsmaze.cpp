#include <maze.h>

DFSMaze::DFSMaze() : StaticMaze(true)
{
    generate();
}

DFSMaze::DFSMaze(int h, int w) : StaticMaze(2*h+1, 2*w+1, true)
{
    generate();
}

DFSMaze::~DFSMaze(){}

void DFSMaze::generate()
{
    setUsed(height, width);
    random_dfs(1, 1);

    set_start();
    set_exit(0.75);
    set_map();
    set_coins(2);
}

void DFSMaze::random_dfs(int x, int y) // Рекурсивный алгоритм "случайного" поиска вглубину
{
    used[x][y] = true;
    int route;

    do // цикл выполняется, пока есть куда генерировать
    {
        route = rand()%4;
        switch(route)
        {
            case 0: // выбрано направление "влево"
            {
                if(y-1 >= 0 && !used[x][y-1])
                {
                    maze[2*x+1][2*y] = EMPTY;
                    random_dfs(x, y-1);
                }
                break;
            }
            case 1: // выбрано направление "вправо"
            {
                if(y+1 < (width-1)/2 && !used[x][y+1])
                {
                    maze[2*x+1][2*y+2] = EMPTY;
                    random_dfs(x, y+1);
                }
                break;
            }
            case 2: // выбрано направление "вверх"
            {
                if(x-1 >= 0 && !used[x-1][y])
                {
                    maze[2*x][2*y+1] = EMPTY;
                    random_dfs(x-1, y);
                }
                break;
            }
            case 3: // выбрано направление "вниз"
            {
                if(x+1 < (height-1)/2 && !used[x+1][y])
                {
                    maze[2*x+2][2*y+1] = EMPTY;
                    random_dfs(x+1, y);
                }
                break;
            }
        }
    }
    while((x-1 >= 0     	  && !used[x-1][y]) ||
          (x+1 < (height-1)/2 && !used[x+1][y]) ||
          (y-1 >= 0     	  && !used[x][y-1]) ||
          (y+1 < (width-1)/2  && !used[x][y+1])   );
}

QRectF DFSMaze::boundingRect() const
{
    return QRectF(width*CELLSIZE/2, height*CELLSIZE/2, 0, 0);
}

void DFSMaze::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            switch(maze[i][j])
            {
                case WALL:
                {
                    painter->setPen(Qt::black);
                    painter->setBrush(Qt::black);
                    painter->drawRect(CELLSIZE*j, CELLSIZE*i, CELLSIZE, CELLSIZE);
                    break;
                }
                case EMPTY:
                {
                    break;
                }
                case WAY:
                {
                    if(USE_HELP)
                    {
                        painter->setPen(Qt::green);
                        painter->setBrush(Qt::green);
                        painter->drawRect(CELLSIZE*j+(CELLSIZE>>2), CELLSIZE*i+(CELLSIZE>>2), (CELLSIZE>>1), (CELLSIZE>>1));
                    }
                    break;
                }
                case FINISH:
                {
                    painter->setPen(Qt::blue);
                    painter->setBrush(Qt::blue);
                    painter->drawEllipse(CELLSIZE*j+(CELLSIZE>>2), CELLSIZE*i+(CELLSIZE>>2), (CELLSIZE>>2)*3, (CELLSIZE>>2)*3);
                    break;
                }
                case CHARACTER:
                {
                    painter->setPen(Qt::black);
                    painter->setBrush(Qt::red);
                    painter->drawEllipse(CELLSIZE*j+(CELLSIZE>>2), CELLSIZE*i+(CELLSIZE>>2), (CELLSIZE>>2)*3, (CELLSIZE>>2)*3);
                    break;
                }
                case COIN:
                {
                    painter->setPen(Qt::blue);
                    painter->setBrush(Qt::yellow);
                    painter->drawEllipse(CELLSIZE*j+(CELLSIZE>>2), CELLSIZE*i+(CELLSIZE>>2), (CELLSIZE>>2)*3, (CELLSIZE>>2)*3);
                    break;
                }
                case CHAR_ON_FIN:
                {
                    painter->setPen(Qt::black);
                    painter->setBrush(Qt::green);
                    painter->drawEllipse(CELLSIZE*j+(CELLSIZE>>2), CELLSIZE*i+(CELLSIZE>>2), (CELLSIZE>>2)*3, (CELLSIZE>>2)*3);
                    break;
                }
            }
        }
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

int DFSMaze::character_move(int dx, int dy) // Слот для реализации перемещения персонажа
{
    int ret = 0;
    int x = character.x;
    int y = character.y;

    switch(maze[x+dx][y+dy])
    {
        case EMPTY:
        {
            if(maze[x][y] == CHAR_ON_FIN)
            {
                maze[x][y] = FINISH;
            }
            else
            {
                maze[x][y] = WAY;
            }
            maze[x+dx][y+dy] = CHARACTER;
            character = {x+dx, y+dy};
            break;
        }
        case WALL:
        {
            break;
        }
        case WAY:
        {
            maze[x][y] = EMPTY;
            maze[x+dx][y+dy] = CHARACTER;
            character = {x+dx, y+dy};
            break;
        }
        case COIN:
        {
            ret += 10;
            if(maze[x][y] == CHAR_ON_FIN)
            {
                maze[x][y] = FINISH;
            }
            else
            {
                maze[x][y] = WAY;
            }
            maze[x+dx][y+dy] = CHARACTER;
            character = {x+dx, y+dy};
            break;
        }
        case FINISH:
        {
            maze[x][y] = EMPTY;
            maze[x+dx][y+dy] = CHAR_ON_FIN;
            character = finish;
            ret += 1;
            break;
        }
    }

    return ret;
}

void DFSMaze::ReGen()
{
    createMazePattern(height, width, true);
    generate();
}

void DFSMaze::set_start() // Установление стартовой ячейки
{
    int sx = 0;
    int sy = 0;
    while(maze[sx][sy] == WALL) // Ищем первую случайную свободную ячейку
    {
        sx = rand()%(height-1) + 1;
        sy = rand()%(width-1) + 1;
    }
    start = {sx, sy};
    character = start;
    maze[sx][sy] = CHARACTER;
}

void DFSMaze::set_exit(double range)  // Устанавливаем конечную вершину
{
    setUsed(height, width);
    DEQUE< pair <Vertex, int> > deq;     // Используем собственную двустороннюю очередь для bfs
    deq.push_back( make_pair(start, 0) );

    int max_range = 0;    // максимальное расстояние, достижимое в лабиринте от start
    while( !deq.empty() ) // поиск max_range
    {
        pair<Vertex, int> cur = deq.front();
        deq.pop_front();
        int x = cur.first.x;
        int y = cur.first.y;
        int cur_range = cur.second;
        Vertex next;
        used[x][y] = true;

        max_range = cur_range;

        if(maze[x-1][y] != WALL && !used[x-1][y])
        {
            next.x = x-1;
            next.y = y;
            used[x-1][y] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(maze[x+1][y] != WALL && !used[x+1][y])
        {
            next.x = x+1;
            next.y = y;
            used[x+1][y] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(maze[x][y-1] != WALL && !used[x][y-1])
        {
            next.x = x;
            next.y = y-1;
            used[x][y-1] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(maze[x][y+1] != WALL && !used[x][y+1])
        {
            next.x = x;
            next.y = y+1;
            used[x][y+1] = true;
            deq.push_back( make_pair(next, cur_range+1));
        }
    }

    // устанавливаем расстояние на котором будет находится выход
    int exit_range = min((double)max_range, (double)(max_range)*range);

    deq.push_back( make_pair(start, 0) );
    setUsed(height, width);

    while(deq.front().second < exit_range)//ищем все точки, удалённые от стартовой на exit_range
    {
        pair<Vertex, int> cur = deq.front();
        deq.pop_front();
        int x = cur.first.x;
        int y = cur.first.y;
        int cur_range = cur.second;
        Vertex next;
        used[x][y] = true;

        if(!used[x-1][y] && maze[x-1][y] == EMPTY)
        {
            next = {x-1, y};
            used[x-1][y] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(!used[x+1][y] && maze[x+1][y] == EMPTY)
        {
            next = {x+1, y};
            used[x+1][y] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(!used[x][y-1] && maze[x][y-1] == EMPTY)
        {
            next = {x, y-1};
            used[x][y-1] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(!used[x][y+1] && maze[x][y+1] == EMPTY)
        {
            next = {x, y+1};
            used[x][y+1] = true;
            deq.push_back( make_pair(next, cur_range+1));
        }
    }

    int choise = rand()%(deq.getSize()); //теперь выбираем рандомную вершину из хранящихся в deq

    for(int i = 0; i < choise; i++)
    {
        deq.pop_front();
    }

    finish = deq.front().first;        // установили вершину выхода
    maze[finish.x][finish.y] = FINISH;
}

void DFSMaze::set_map()  // Ищем путь от старта до финиша (нужно для подсказки)
{
    setUsed(height, width);

    DEQUE< Vertex > deq;    // Используем собственную двустороннюю очередь для dfs
    deq.push_back(finish);

    for(;;) 				// Собственно, сам dfs
    {
        Vertex cur = deq.back();
        if(cur.x == start.x && cur.y == start.y) break;
        int x = cur.x;
        int y = cur.y;

        if(x != finish.x || y != finish.y) maze[x][y] = WAY;
        used[x][y] = true;

        if( (!used[x-1][y] && maze[x-1][y] != WALL) ||
            (!used[x+1][y] && maze[x+1][y] != WALL) ||
            (!used[x][y-1] && maze[x][y-1] != WALL) ||
            (!used[x][y+1] && maze[x][y+1] != WALL) )
        {
            Vertex next;
            if(x-1 > 0 && !used[x-1][y] && (maze[x-1][y] == EMPTY || maze[x-1][y] == CHARACTER))
            {
                next = {x-1, y};
                deq.push_back(next);
            }
            if(x+1 < height-1 && !used[x+1][y] && (maze[x+1][y] == EMPTY || maze[x+1][y] == CHARACTER))
            {
                next = {x+1, y};
                deq.push_back(next);
            }
            if(y-1 > 0 && !used[x][y-1] && (maze[x][y-1] == EMPTY || maze[x][y-1] == CHARACTER))
            {
                next = {x, y-1};
                deq.push_back(next);
            }
            if(y+1 < width-1 && !used[x][y+1] && (maze[x][y+1] == EMPTY || maze[x][y+1] == CHARACTER))
            {
                next = {x, y+1};
                deq.push_back(next);
            }
        }
        else
        {
            maze[x][y] = EMPTY;
            deq.pop_back();
        }
    }
}
