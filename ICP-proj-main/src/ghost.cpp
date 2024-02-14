#include "ghost.h"
#include <QGraphicsScene>
#include <cstdlib>
#include <ctime>
#include <QApplication>
#include <cstdlib>
#include <iostream>

Ghost::Ghost(MazeObject* mazeGhost, Maze* maze, QTimer *mainTimer, int ghostOrder, QObject *parent) :
    QObject(parent),
    QGraphicsPixmapItem(),
    m_maze(maze),
    m_timer(new QTimer(this))
{
    m_mazeObject = mazeGhost;
    QPixmap pixmap("images/ghost.png");
    setPixmap(pixmap.scaled(QSize(60, 60), Qt::KeepAspectRatio));

    // set up a timer to move the ghost every 500 milliseconds
    QTimer *m_timer = mainTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(move()));
    rows = maze->getRows()-2;
    cols = maze->getCols()-2;
    seed = ghostOrder;
}

void Ghost::move()
{
    // get the current row and column of the ghost in the maze
    int currentCol = pos().x() / m_step;
    int currentRow = pos().y() / m_step;
    // generate a random direction (up, down, left, or right)
    srand(time(nullptr) * seed);
    int direction = rand() % 4;

    // attempt to move the ghost in the chosen direction
    switch (direction) {
    case 0: // up
        if (m_mazeObject->move(Direction::U)) {
            if(currentRow > 0){
                setPos(currentCol * m_step, (currentRow - 1) * m_step);
            }
        }
        break;
    case 1: // down
        if (m_mazeObject->move(Direction::D)) {
            if(currentRow < rows){
            setPos(currentCol * m_step, (currentRow + 1) * m_step);
            }
        }
        break;
    case 2: // left
        if (m_mazeObject->move(Direction::L)) {
            if(currentCol > 0){
                setPos((currentCol - 1) * m_step, currentRow * m_step);
            }
        }
        break;
    case 3: // right
        if (m_mazeObject->move(Direction::R)) {
            if(currentCol < cols){
                setPos((currentCol + 1) * m_step, currentRow * m_step);
            }
        }
        break;
    }
}
