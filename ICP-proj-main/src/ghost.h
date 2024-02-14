/**
 * @file Ghost.h
 * @brief Header file for the Ghost class, which represents a ghost character in a Pac-Man game.
 */

#ifndef GHOST_H
#define GHOST_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include "headers/MazeObject.hpp"
#include "headers/Maze.hpp"

/**
 * @class Ghost
 * @brief Represents the view of a ghost character in a Pac-Man game.
 *
 * The Ghost class is a subclass of QObject and QGraphicsPixmapItem, and
 * represents a ghost character in a Pac-Man game. It is responsible for moving
 * around the game board and avoiding collisions with the player character and
 * other ghosts.
 */
class Ghost : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a Ghost object with the given parameters.
     * @param mazeObject A pointer to the MazeObject that contains the ghost's starting position.
     * @param maze A pointer to the Maze object that represents the game board.
     * @param mainTimer A QTimer object that controls the main game loop.
     * @param ghostOrder An integer that represents the ghost's order. There are ghosts. 
     * @param parent An optional parent QObject.
     */
    explicit Ghost(MazeObject* mazeObject, Maze* maze, QTimer *mainTimer, int ghostOrder, QObject *parent = nullptr);

public slots:
    /**
     * @brief Moves the ghost one step in its current direction.
     *
     * This slot function is called by the main game loop to move the ghost one
     * step in its current direction.
     */
    void move();

private:
    int rows; /**< The number of rows in the game board. */
    int cols; /**< The number of columns in the game board. */
    MazeObject* m_mazeObject; /**< A pointer to the MazeObject that contains the ghost's current position. */
    Maze* m_maze; /**< A pointer to the Maze object that represents the game board. */
    QTimer* m_timer; /**< A QTimer object that controls the ghost's movement. MainLoop */
    const int m_step = 50; /**< The distance (in pixels) that the ghost moves in each step. */
    int seed; /**< A random seed value used to generate the ghost's movement pattern. */
};

#endif // GHOST_H
