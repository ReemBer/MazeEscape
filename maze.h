#ifndef MAZE_H
#define MAZE_H

#include "deque.h"
#include <random>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>

using namespace std;

class Maze : public QObject, public QGraphicsItem// базовый, абстрактный класс
{    
protected:

    enum Cell  // Перечисление, отвечающее за состояние ячейки лабиринта
    {
        // Ниже перечислены состояния ячеек лабиринта, сгенерированного алгоритмом "deepth-first search"

        EMPTY,                 // ячейка, свободная для прохода
        WALL,                  // стенка лабиринта
        WAY,                   // "ячейки-подсказки" для построения пути
        COIN,                  // "Монетка" - бонус
        CHARACTER,             // Положение персонажа
        FINISH,                // Выход из лабиринта
        CHAR_ON_FIN,           // Состояние, когда персонаж находится на выходе
    };

    typedef struct Vertex // Структура, хранящая координаты некоторой вершины
    {
        int x;
        int y;
    } Vertex;

protected:
    int   height = 0;
    int   width  = 0;
    Cell  **maze; // Сам лабиринт -- двумерный, динамиеский массив

public:
    explicit Maze(QObject *parent = 0);
    ~Maze();

protected:
    virtual void generate() = 0; // общая функция генерации лабиринтов

};


class StaticMaze : public Maze // Построение лабиринта как дерева на матрице
{
protected: // Константы, значения по-умолчанию, флаги.

    const int          HEIGHT = 10;             // Размеры "Заготовки лабиринта" по-умолчанию
    const int          WIDTH = 20;              //

    bool               USE_HELP;                // флаг для отображения подсказок.
    int                CELLSIZE;

protected: // Основные ячейки, необходимые для генерации и самого процесса игры.

    Vertex start = {-1, -1};
    Vertex finish = {-1, -1};
    Vertex character = {-1, -1};

protected: // Матрица "использованных" ячеек (используется для dfs и bfs)

    bool** used   = nullptr;
    int    used_h = 0;
    int    used_w = 0;

protected:

    void createMazePattern(int h, int w, bool f); // построение "заготовки лабиринта"

public:

    explicit StaticMaze(bool f);                       // создание "заготовки лабиринта" по-умолчанию
    explicit StaticMaze(int h, int w, bool f);   // создание "заготовки лабиринта" по заданным размерам
    void set_way_visible(bool);
    ~StaticMaze();

protected:

    virtual int character_move(int, int) = 0;

protected: // вспомогательные функции генерации

    void setUsed(int h, int w);         // "зануление" матрицы used (подготовка к использованию)
    void clearUsed();                   // отчистка отработанной матрицы
    void set_coins(unsigned int count); // генерация бонусов

    virtual void set_start() = 0;                   // установка стартовой вершины
    virtual void set_exit(double range) = 0;        // установка конечной вершины
    virtual void set_map() = 0;                     // установка начального пути от персонажа до выхода

};

class DFSMaze : public StaticMaze
{
public:

    explicit DFSMaze();
    DFSMaze(int h, int w);
    ~DFSMaze();

public:


    // Функции отрисовки лабиринта
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:

    int character_move(int, int);       // перемещение персонажа
    void generate();                    // Основная функция генерации лабиринта

signals:

    void gameOver();
    void coinCheck();

public slots:

    void ReGen();

private:

    void random_dfs(int, int);  // "случайный" поиск в глубину

    void set_start();
    void set_exit(double range);
    void set_map();
};


class EllerMaze : public StaticMaze
{
    enum EllCell
    {
        NO_WALL,               // Ячейка без стенок
        RIGHT_WALL,            // Ячейка с правой стенкой
        DOWN_WALL,             // Ячейка с нижней стенкой
        RIGHT_DOWN_WALL        // Ячейка, имеющая стены внизу и справа
    };

private:

    EllCell **ellMaze;

    int       *cntWithDown;   // используется для подсчёта ячеек с нижней границей
    int       *numberSets;    // i-ая ячейка -- номер множества i-ой клетки строки
    int       *set;           // i-ый элемент - количество ячеек i-ого множества
    int       *genStr;        // текущая строка генерации лабиринта
                              // кодирование состояний ячеек genStr:
                              // 0 -- нет стенок;
                              // 1 -- есть стенка справа;
                              // 10 - есть стенка снизу;
                              // 11 - есть стенки справа и снизу.
public:

    EllerMaze();
    EllerMaze(int h, int w);
    ~EllerMaze();

public slots:

    void ReGen();

protected:

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:

    int character_move(int, int);
    void generate();

private: // Основные функции генерации

    void startGen();                // начало генерации
    void setUniqSet(int position);  // устанавливаем уникальные множества для ячеек
    void genCurString();            // генерируем текущую строку
    void genRightWall();            // генерируем правые границы
    void genDownWall();             // генерируем нижние границы
    void setCurString(int x);       // вставляем текущую строку в лабиринт
    void cleanWalls();              // удаляем границцы
    void completeLastString();      // дополняем последнюю строку -- завершаем лабиринт

private: // Расстановка игровых компонент по лабиринту

    void set_start();
    void set_exit(double range);
    void set_map();
};

#endif // MAZE_H
