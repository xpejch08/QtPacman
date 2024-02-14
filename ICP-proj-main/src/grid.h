/**
 * @Author xpejch08 Štěpán Pejchar 
 * @file Grid.h
 * @brief Header file for the Grid class, which represents the game board in a Pac-Man game.
 */

#ifndef GRID_H
#define GRID_H

#include <QGraphicsItem>
#include <headers/MazeObject.hpp>

/**
 * @class Grid
 * @brief Represents the game board in a Pac-Man game.
 *
 * The Grid class is a QGraphicsItem that represents the game board in a Pac-Man game.
 * It is responsible for drawing the maze and the player and ghost characters on the screen.
 */
class Grid : public QGraphicsItem
{
public:
    /**
     * @brief Constructs a Grid object with the given parameters.
     * @param maze A pointer to the Maze object that represents the game board.
     * @param parent An optional parent QGraphicsItem.
     */
    Grid(Maze *maze, QGraphicsItem *parent = nullptr);

    Maze *mazeGrid; /**< A pointer to the Maze object that represents the game board. */
    int rows; /**< The number of rows in the game board. */
    int cols; /**< The number of columns in the game board. */

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief Paints the log messages on the screen.
     * @param painter A QPainter object used for painting.
     * @param option A QStyleOptionGraphicsItem object.
     * @param widget A QWidget object.
     */
    void paintLog(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int m_cellSize; /**< The size of each cell (in pixels) on the game board. */
};

#endif // GRID_H
