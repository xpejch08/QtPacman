/**
 * @author xpejch08 Štěpán Pejchar
 * @file GridLog.h
 * @brief Header file for the GridLog class, which represents the game board log in a Pac-Man game.
 */

#ifndef GRIDLOG_H
#define GRIDLOG_H

#include <iostream>
#include <fstream>
#include <QGraphicsItem>
#include <headers/MazeObject.hpp>

/**
 * @class GridLog
 * @brief Represents the game board log in a Pac-Man game.
 *
 * The GridLog class is a QGraphicsItem that represents the game board log in a Pac-Man game.
 * It is responsible for reading the log files and drawing the log messages on the screen.
 */
class GridLog : public QGraphicsItem
{
public:
    /**
     * @brief Constructs a GridLog object with the given parameters.
     * @param maze A pointer to the Maze object that represents the game board.
     * @param parent An optional parent QGraphicsItem.
     */
    GridLog(Maze *maze, QGraphicsItem *parent = nullptr);

    Maze *mazeGrid; /**< A pointer to the Maze object that represents the game board. */
    int rows; /**< The number of rows in the game board. */
    int cols; /**< The number of columns in the game board. */
    int logfilesCount; /**< The number of log files to read. */
    std::ifstream file; /**< An input file stream used for reading the log files. */

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief Reads the maze from the log file.
     * @return Succes or not.
     */
    int readMaze();


private:
    int m_cellSize; /**< The size of each cell (in pixels) on the game board. */
};

#endif // GRIDLOG_H
