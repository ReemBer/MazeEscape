#include <maze.h>

EllerMaze::EllerMaze() : StaticMaze(false)
{
    try
    {
        ellMaze = new EllCell*[HEIGHT];
        if(!ellMaze) throw 1;
        for(int i = 0; i < HEIGHT; i++)
        {
            ellMaze[i] = new EllCell[WIDTH];
            if(!ellMaze[i]) throw 2;
            for(int j = 0; j < WIDTH; j++)
            {
                ellMaze[i][j] = NO_WALL;
            }
        }
        generate();
    }
    catch(int i)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("FATAL ERROR In constructor EllerMaze() NOT ENOUGTH MEMORY");
        m->exec();
        terminate();
    }
}

EllerMaze::EllerMaze(int h, int w) : StaticMaze(h, w, false)
{
    try
    {
        ellMaze = new EllCell*[h];
        if(!ellMaze) throw 1;
        for(int i = 0; i < h; i++)
        {
            ellMaze[i] = new EllCell[w];
            if(!ellMaze[i]) throw 2;
            for(int j = 0; j < w; j++)
            {
                ellMaze[i][j] = NO_WALL;
            }
        }
        generate();
    }
    catch(int i)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("FATAL ERROR In constructor EllerMaze(h, w) : NOT ENOUGTH MEMORY");
        m->exec();
        terminate();
    }
}

EllerMaze::~EllerMaze()
{
    delete[] set;
    delete[] numberSets;
    delete[] cntWithDown;
    delete[] genStr;
    for(int i = height-1; i >= 0; i++)
    {
        delete[] ellMaze[i];
    }
    delete[] ellMaze;
}

void EllerMaze::startGen() // начало генерации
{
    try
    {
        cntWithDown = new int[width+1];
        set         = new int[width+1];
        numberSets  = new int[width+1];
        genStr      = new int[width+1];
        if(!genStr || !numberSets || !set || !cntWithDown) throw 1;
    }
    catch(int i)
    {
        QMessageBox *m = new QMessageBox();
        m->setText("FATAL ERROR In function startGen : NOT ENOUGTH MEMORY");
        m->exec();
        terminate();
    }
    for(int i = 0; i <= width; i++) // Ни одна ячейка не принадлежит ниодному множеству
    {
        cntWithDown[i] = set[i] = numberSets[i] = genStr[i] = 0;
    }
}

void EllerMaze::setUniqSet(int position) // устанавливаем уникальные множества для ячеек
{
    try
    {
       if(position > width) throw 1;
       if(position < 0)      throw 1.0;
       for(int i = 1; i <= width; i++)
       {
           if(!set[i]) // текущее множество ещё не занято
           {
               set[i]++;
               numberSets[position] = i;
               return;
           }
       }
    }
    catch(int i)
    {
       numberSets[width-1] = rand()%width;
       QMessageBox *m = new QMessageBox();
       m->setText("Error in function setUniqSet: Index out of bounds");
       m->exec();
    }
    catch(double i)
    {
        numberSets[0] = rand()%width;
        QMessageBox *m = new QMessageBox();
        m->setText("Error in function setUniqSet: Index out of bounds");
        m->exec();
    }
}

void EllerMaze::genCurString() // генерируем текущую строку
{
    for(int i = 1; i <= width; i++)
    {
        if(!numberSets[i]) // Ячейкам, не принадлежащем ниодному множеству присвоим своё уникальное множество
        {
            setUniqSet(i);
        }
    }

    genStr[width]++; // самая правая ячейка имеет границу справа всегда

    genRightWall();
    genDownWall();
}

void EllerMaze::genRightWall() // генерируем правые границы
{
    for(int i = 1; i < width; i++) // генерируем правые границы
    {
        if(numberSets[i] == numberSets[i+1])
        {
            genStr[i]++;
        }
        else
        {
            int choice = rand()%3; // случайно решим, добавлять ли границу
            switch(choice)
            {
                case 0: case 2: // решили не добавлять границу
                {
                    for(int j = 1; j <= width; j++)
                    {
                        if(j != i+1 && numberSets[i+1] == numberSets[j])
                        {
                            set[numberSets[i]]++;
                            set[numberSets[j]]--;
                            numberSets[j] = numberSets[i];
                        }
                    }
                    set[numberSets[i]]++;
                    set[numberSets[i+1]]--;
                    numberSets[i+1] = numberSets[i];
                    break;
                }
                case 1: // решили добавить границу
                {
                    if(!genStr[i]) genStr[i]++;
                    break;
                }
            }
        }
    }
}

void EllerMaze::genDownWall() // генерируем нижние границы
{
    for(int i = 1; i <= width; i++)
    {
        int choice = rand()%5; // случайно решим, добавлять ли границу
        switch(choice)
        {
            case 0: case 1: // решили не добавлять границу
            {
                break;
            }
            case 2: case 3: case 4: // решили добавить границу
            {
                if(cntWithDown[numberSets[i]] < set[numberSets[i]]-1)
                {
                    genStr[i] += 10;
                    cntWithDown[numberSets[i]]++;
                }
                break;
            }
        }
    }
}

void EllerMaze::setCurString(int x) // вставляем текущую строку в лабиринт
{
    for(int y = 0; y < width; y++) // запишем сгенерированную строку в ellMaze
    {
        switch(genStr[y+1])
        {
            case 0:
            {
                ellMaze[x][y] = NO_WALL;
                break;
            }
            case 1:
            {
                ellMaze[x][y] = RIGHT_WALL;
                break;
            }
            case 10:
            {
                ellMaze[x][y] = DOWN_WALL;
                break;
            }
            case 11:
            {
                ellMaze[x][y] = RIGHT_DOWN_WALL;
                break;
            }
        }
    }
}

void EllerMaze::cleanWalls() // удаляем границцы
{
    for(int i = 1; i <= width; i++)
    {
        if((genStr[i]%10)) genStr[i]--; // Удаляем правые границы

        if((genStr[i]/10))       // если в ячейке есть нижняя граница
        {
            set[numberSets[i]]--;          // удалим ячейку из её множества
            cntWithDown[numberSets[i]]--;  // уменьшим число ячеек с нижней границев в текущем множестве
            numberSets[i] = 0;             // обнулим множество i-ой ячейки
            genStr[i] -= 10;               // удалим нижнюю ячейку из клетки
        }
    }
}

void EllerMaze::completeLastString() // дополняем последнюю строку -- завершаем лабиринт
{
    for(int i = 1; i <= width; i++) // каждая ячейка имеет границу снизу
    {
        if(!(genStr[i]/10)) genStr[i] += 10;
    }

    for(int i = 1; i < width; i++) // удаляем ненужные границы справа
    {
        if(numberSets[i] != numberSets[i+1])
        {
            if((genStr[i]%10)) // если есть правая граница, удаляем её
            {
                genStr[i]--;
            }
                for(int j = 1; j <= width; j++)
                {
                    if(j != i+1 && numberSets[i+1] == numberSets[j])
                    {
                        set[numberSets[i]]++;
                        set[numberSets[j]]--;
                        numberSets[j] = numberSets[i];
                    }
                }
                set[numberSets[i]]++;
                set[numberSets[i+1]]--;
                numberSets[i+1] = numberSets[i];
        }
    }
}

void EllerMaze::generate()
{
    startGen();
    for(int x = 0; x < height; x++) // Генерируем строки лабиринта
    {
        genCurString();
        if(x == height-1) break;    // последнюю строку нужно дополнить, прежде чем добавить в лабиринт
        setCurString(x);
        cleanWalls();
    }
    completeLastString();           // дополняем последнюю ячейку
    setCurString(height-1);

    set_start();             // Устанавливаем стартовую вершину
    set_exit(1.0);  // Устанавливаем выход в лабиринте
    set_map();
}

void EllerMaze::ReGen()
{
    createMazePattern(height, width, false);
    generate();
}

QRectF EllerMaze::boundingRect() const
{
    return QRectF(width*CELLSIZE/2, height*CELLSIZE/2, 0, 0);
}

void EllerMaze::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(!j)
            {
                painter->setPen(Qt::black);
                painter->drawLine(CELLSIZE*j, CELLSIZE*i, CELLSIZE*j, CELLSIZE*(i+1));
            }
            if(!i)
            {
                painter->setPen(Qt::black);
                painter->drawLine(CELLSIZE*j, CELLSIZE*i, CELLSIZE*(j+1), CELLSIZE*i);
            }
            switch(ellMaze[i][j])
            {
                case RIGHT_WALL:
                {
                    painter->setPen(Qt::black);
                    painter->setBrush(Qt::black);
                    painter->drawLine(CELLSIZE*(j+1), CELLSIZE*i, CELLSIZE*(j+1), CELLSIZE*(i+1));
                    break;
                }
                case NO_WALL:
                {
                    break;
                }
                case DOWN_WALL:
                {
                    painter->setPen(Qt::black);
                    painter->setBrush(Qt::black);
                    painter->drawLine(CELLSIZE*j, CELLSIZE*(i+1), CELLSIZE*(j+1), CELLSIZE*(i+1));
                    break;
                }
                case RIGHT_DOWN_WALL:
                {
                    painter->setPen(Qt::black);
                    painter->setBrush(Qt::black);
                    painter->drawLine(CELLSIZE*(j+1), CELLSIZE*i, CELLSIZE*(j+1), CELLSIZE*(i+1));
                    painter->drawLine(CELLSIZE*j, CELLSIZE*(i+1), CELLSIZE*(j+1), CELLSIZE*(i+1));
                    break;
                }
                default:
                {
                    painter->setPen(Qt::blue);
                    painter->setBrush(Qt::blue);
                    painter->drawEllipse(CELLSIZE*j, CELLSIZE*i, CELLSIZE, CELLSIZE);
                }
            }

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

void EllerMaze::set_start() // Установление стартовой ячейки
{
    int sx = rand()%height;
    int sy = rand()%width;
    start = {sx, sy};
    character = start;
    maze[sx][sy] = CHARACTER;
}

void EllerMaze::set_exit(double range)  // Устанавливаем конечную вершину
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

        if(x-1 >= 0 && ellMaze[x-1][y] != DOWN_WALL && ellMaze[x-1][y] != RIGHT_DOWN_WALL && !used[x-1][y])
        {
            next = {x-1, y};
            used[x-1][y] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(x+1 < height && ellMaze[x][y] != DOWN_WALL && ellMaze[x][y] != RIGHT_DOWN_WALL && !used[x+1][y])
        {
            next = {x+1, y};
            used[x+1][y] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(y-1 >= 0 && ellMaze[x][y-1] != RIGHT_WALL && ellMaze[x][y-1] != RIGHT_DOWN_WALL && !used[x][y-1])
        {
            next = {x, y-1};
            used[x][y-1] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(y+1 < width && ellMaze[x][y] != RIGHT_WALL && ellMaze[x][y] != RIGHT_DOWN_WALL && !used[x][y+1])
        {
            next = {x, y+1};
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

        if(x-1 >= 0 && !used[x-1][y] && ( ellMaze[x-1][y] == NO_WALL || ellMaze[x-1][y] == RIGHT_WALL))
        {
            next = {x-1, y};
            used[x-1][y] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(x+1 < height && !used[x+1][y] && ( ellMaze[x][y] == NO_WALL || ellMaze[x][y] == RIGHT_WALL))
        {
            next = {x+1, y};
            used[x+1][y] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(y-1 >= 0 && !used[x][y-1] && ( ellMaze[x][y-1] == NO_WALL || ellMaze[x][y-1] == DOWN_WALL))
        {
            next = {x, y-1};
            used[x][y-1] = true;
            deq.push_back( make_pair(next, cur_range+1) );
        }
        if(y+1 < width && !used[x][y+1] && ( ellMaze[x][y] == NO_WALL || ellMaze[x][y] == DOWN_WALL))
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

void EllerMaze::set_map()  // Ищем путь от старта до финиша (нужно для подсказки)
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

        if( (x-1 >= 0 && !used[x-1][y] && ( ellMaze[x-1][y] == NO_WALL || ellMaze[x-1][y] == RIGHT_WALL)) ||
            (x+1 < height && !used[x+1][y] && ( ellMaze[x][y] == NO_WALL || ellMaze[x][y] == RIGHT_WALL)) ||
            (y-1 >= 0 && !used[x][y-1] && ( ellMaze[x][y-1] == NO_WALL || ellMaze[x][y-1] == DOWN_WALL)) ||
            (y+1 < width &&!used[x][y+1] && ( ellMaze[x][y] == NO_WALL || ellMaze[x][y] == DOWN_WALL)) )
        {
            Vertex next;
            if(x-1 >= 0 && !used[x-1][y] && ( ellMaze[x-1][y] == NO_WALL || ellMaze[x-1][y] == RIGHT_WALL))
            {
                next = {x-1, y};
                deq.push_back(next);
            }
            if(x+1 < height && !used[x+1][y] && ( ellMaze[x][y] == NO_WALL || ellMaze[x][y] == RIGHT_WALL))
            {
                next = {x+1, y};
                deq.push_back(next);
            }
            if(y-1 >= 0 && !used[x][y-1] && ( ellMaze[x][y-1] == NO_WALL || ellMaze[x][y-1] == DOWN_WALL))
            {
                next = {x, y-1};
                deq.push_back(next);
            }
            if(y+1 < width && !used[x][y+1] && ( ellMaze[x][y] == NO_WALL || ellMaze[x][y] == DOWN_WALL))
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

int EllerMaze::character_move(int dx, int dy)
{
    int ret = 0;
    int x = character.x;
    int y = character.y;

    if(dy == -1)
    {
        if(y-1 < 0);
        else if(ellMaze[x][y-1] == RIGHT_WALL || ellMaze[x][y-1] == RIGHT_DOWN_WALL);
        else
        {
            character = {x+dx, y+dy};

            if(maze[x][y] == CHAR_ON_FIN)
            {
                maze[x][y] = FINISH;
            }
            else if( maze[x][y-1] == WAY)
            {
                maze[x][y] = EMPTY;
            }
            else
            {
                maze[x][y] = WAY;
            }

            if(maze[x][y-1] == FINISH)
            {
                maze[x][y-1] = CHAR_ON_FIN;
                maze[x][y] = EMPTY;
                ret = 1;
            }
            else
            {
                maze[x][y-1] = CHARACTER;
            }
        }
    }
    else if(dy == 1)
    {
        if(y+1 >= width);
        else if(ellMaze[x][y] == RIGHT_WALL || ellMaze[x][y] == RIGHT_DOWN_WALL);
        else
        {
            character = {x+dx, y+dy};

            if(maze[x][y] == CHAR_ON_FIN)
            {
                maze[x][y] = FINISH;
            }
            else if( maze[x][y+1] == WAY)
            {
                maze[x][y] = EMPTY;
            }
            else
            {
                maze[x][y] = WAY;
            }

            if(maze[x][y+1] == FINISH)
            {
                maze[x][y+1] = CHAR_ON_FIN;
                maze[x][y] = EMPTY;
                ret = 1;
            }
            else
            {
                maze[x][y+1] = CHARACTER;
            }
        }
    }
    else if(dx == -1)
    {
        if(x-1 < 0);
        else if(ellMaze[x-1][y] == DOWN_WALL || ellMaze[x-1][y] == RIGHT_DOWN_WALL);
        else
        {
            character = {x+dx, y+dy};

            if(maze[x][y] == CHAR_ON_FIN)
            {
                maze[x][y] = FINISH;
            }
            else if( maze[x-1][y] == WAY)
            {
                maze[x][y] = EMPTY;
            }
            else
            {
                maze[x][y] = WAY;
            }

            if(maze[x-1][y] == FINISH)
            {
                maze[x-1][y] = CHAR_ON_FIN;
                maze[x][y] = EMPTY;
                ret = 1;
            }
            else
            {
                maze[x-1][y] = CHARACTER;
            }
        }
    }
    else if(dx == 1)
    {
        if(x+1 >= height);
        else if(ellMaze[x][y] == DOWN_WALL || ellMaze[x][y] == RIGHT_DOWN_WALL);
        else
        {
            character = {x+dx, y+dy};

            if(maze[x][y] == CHAR_ON_FIN)
            {
                maze[x][y] = FINISH;
            }
            else if( maze[x+1][y] == WAY)
            {
                maze[x][y] = EMPTY;
            }
            else
            {
                maze[x][y] = WAY;
            }

            if(maze[x+1][y] == FINISH)
            {
                maze[x+1][y] = CHAR_ON_FIN;
                maze[x][y] = EMPTY;
                ret = 1;
            }
            else
            {
                maze[x+1][y] = CHARACTER;
            }
        }
    }
    return ret;
}
