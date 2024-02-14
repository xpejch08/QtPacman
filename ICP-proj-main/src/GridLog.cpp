#include "gridLog.h"
#include "qdebug.h"
#include <QPainter>
#include <iostream>
#include <fstream>

GridLog::GridLog(Maze * maze, QGraphicsItem *parent) : QGraphicsItem(parent), m_cellSize(50)
{
    mazeGrid = maze;
    rows = mazeGrid->getRows() - 1;
    cols = mazeGrid->getCols() - 1;
}

QRectF GridLog::boundingRect() const
{
    return QRectF(0, 0, m_cellSize * rows, m_cellSize * cols);
}

void GridLog::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    readMaze();
    painter->setPen(Qt::red);
    MazeObject * tmp;
    bool wall = true;
    for (int x = 0; x <= rows; ++x) {
        for (int y = 0; y <= cols; ++y) {
            wall = mazeGrid->getField(y, x)->canMove();
            tmp = mazeGrid->getField(y, x)->get();
            //wall
            if(!wall && tmp == NULL){
                wall = true;
                QRectF cellRect((x-1) * m_cellSize, (y-1) * m_cellSize, m_cellSize, m_cellSize);
                painter->setBrush(Qt::red);
                painter->drawRect(cellRect);
            }
            //path
            else if(tmp == NULL){
                QRectF cellRect((x-1) * m_cellSize, (y-1) * m_cellSize, m_cellSize, m_cellSize);
                painter->setBrush(Qt::NoBrush);
                painter->drawRect(cellRect);
            }
            //key
            else if(tmp->isKey()){
                QRectF cellRect((x-1) * m_cellSize, (y-1) * m_cellSize, m_cellSize, m_cellSize);
                painter->setBrush(Qt::blue);
                painter->drawRect(cellRect);
            }
            //end
            else if(tmp->isTarget()){
                QRectF cellRect((x-1) * m_cellSize, (y-1) * m_cellSize, m_cellSize, m_cellSize);
                painter->setBrush(Qt::magenta);
                painter->drawRect(cellRect);
            }
            else if(tmp->isPacman()){
                QRectF cellRect((x-1) * m_cellSize, (y-1) * m_cellSize, m_cellSize, m_cellSize);
                painter->setBrush(Qt::yellow);
                painter->drawRect(cellRect);
            }
            else if(tmp->isGhost()){
                QRectF cellRect((x-1) * m_cellSize, (y-1) * m_cellSize, m_cellSize, m_cellSize);
                painter->setBrush(Qt::green);
                painter->drawRect(cellRect);
            }
        }
    }
}

int GridLog::readMaze(){
    for (int i = 1; i <= logfilesCount; i++) {
        std::string filename = "data/log/" + std::to_string(i) + ".txt";
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            continue; // Move to next iteration if file cannot be opened
        }

    if (file.is_open()){
        std::string str_rows;
        file >> str_rows;
        rows = stoi(str_rows);
        std::string str_cols;
        file >> str_cols;
        cols = stoi(str_cols);

        std::string inputstring;

        mazeGrid->startReading(rows, cols);

        while (file.good()){
            file >> inputstring;
            if (int(inputstring.length()) != cols){
                qDebug() << "wrong input";
                return 1;
            }
            mazeGrid->processLine(inputstring);
        }
    }
    else{
        qDebug() << "couldnt read map\n";
        return 1;
    }
}
