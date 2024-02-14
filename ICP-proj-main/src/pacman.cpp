#include "pacman.h"
#include "qwidget.h"
#include <QTime>
#include <QApplication>
#include <QGraphicsScene>
#include <headers/MazeObject.hpp>
#include <headers/Field.hpp>
#include <QDebug>
#include <QTimer>
#include <QMainWindow>
#include <QLabel>
#include <QGraphicsView>

Pacman::Pacman(MazeObject *pacman, Maze *maze, QTimer *mainTimer, QGraphicsScene *endScene, QMainWindow *endWindow, QGraphicsItem *parent) :QGraphicsItem(parent)
{
    pacmanMove = pacman;
    m_endScene = endScene;
    m_endWindow = endWindow;
    endLabelLoose = new QLabel("You have died,\n If you want to play again\n Restart the game");
    endLabelWin = new QLabel("Good job You have Won,\n If you want to play again\n Restart the game");
    m_maze = maze;
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    m_timer = mainTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(move()));
    rows = maze->getRows() - 2;
    //m_parentWidget = parentOb;
    cols = maze->getCols() - 2;
}

QRectF Pacman::boundingRect() const
{
    return QRectF(0, 0, m_step, m_step);
}

void Pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::yellow);
    painter->drawPie(boundingRect(), 45 * 16, 270 * 16);
}

void Pacman::paintPacman(MazeObject *pacman){
    setPos((pacman->getCols() * 50) - 50, (pacman->getRows() * 50) - 50);
}

void Pacman::move(){
    pacmanMove->steps++;
    setFocus();
    if(pacmanMove->get_lives() == 0){
        m_timer->stop();
        endLabelLoose->setFixedSize(300, 300);
        endLabelLoose->move(0, +200);
        m_endScene->addWidget(endLabelLoose);
        m_endWindow->show();
    }
    if(pacmanMove->isEnd){
        m_timer->stop();
        endLabelWin->setFixedSize(300, 300);
        endLabelWin->move(0, +200);
        m_endScene->addWidget(endLabelWin);
        m_endWindow->show();
    }
    int x = pos().x() / m_step;
    int y = pos().y() / m_step;


    if (lastDir == Direction::L && x > 0) {
        if(pacmanMove->move(Direction::L)){
            paintPacman(pacmanMove);
        }
    }
    else if (lastDir == Direction::R && x < rows) {
        if(pacmanMove->move(Direction::R)){
            paintPacman(pacmanMove);
        }
    }
    else if (lastDir == Direction::U && y > 0) {
        if(pacmanMove->move(Direction::U)){
            paintPacman(pacmanMove);
        }
    }
    else if(lastDir == Direction::D && y < cols) {
        if(pacmanMove->move(Direction::D)){
            paintPacman(pacmanMove);
        }
    }

}

void Pacman::keyPressEvent(QKeyEvent *event)
{
    setFocus();
    qDebug() << "PRESSED";
    int x = pos().x() / m_step;
    int y = pos().y() / m_step;


    if (event->key() == Qt::Key_Left && x > 0) {
        if(pacmanMove->canMove(Direction::L)){
            lastDir = Direction::L;
        }
        //SLOT(moveLeft/canmove)->return next action
        //this->canMove(L);
    } else if (event->key() == Qt::Key_Right && x < rows) {
        if(pacmanMove->canMove(Direction::R)){
            lastDir = Direction::R;
        }
    } else if (event->key() == Qt::Key_Up && y > 0) {
        if(pacmanMove->canMove(Direction::U)){
            lastDir = Direction::U;
        }
    } else if (event->key() == Qt::Key_Down && y < cols) {
        if(pacmanMove->canMove(Direction::D)){
            lastDir = Direction::D;
        }
    } else {
        QGraphicsItem::keyPressEvent(event);
    }

}

