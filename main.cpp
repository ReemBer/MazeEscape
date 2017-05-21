#include "mazeescape.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MazeEscape w;

    w.startGame();

    return a.exec();
}
