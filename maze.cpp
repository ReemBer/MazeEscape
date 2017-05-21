#include "maze.h"

// Здесь просто устанавливаем "начало рандомизации"
Maze::Maze(QObject *parent) : QObject(parent), QGraphicsItem()
{
    height = width = 0;
    srand(time(0));
}

// Освобождаем диинамическую память
Maze::~Maze()
{
    for(int i = height-1; i>= 0; i++)
    {
        delete[] maze[i];
    }
    delete[] maze;
}
