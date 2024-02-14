/**
 * @file MazeObject.hpp
 * @author Jakub Kořínek <xkorin17@stud.fit.vutbr>
 * @brief Header file defining playable objects of maze.
 */

#ifndef MAZEOBJECT_H
#define MAZEOBJECT_H

class MazeObject;

#include "Field.hpp"
#include "Maze.hpp"

/**
 * @class MazeObject
 * @brief class defining playable objects of maze.
 * 
 */
class MazeObject{
private:
    int row;
    int col;
    Maze *maze;
    bool ghost;
    bool pacman;
    bool key;
    bool target;
    int lives;
    bool ownsKey;
    int startRow;
    int startCol;

public:
    int steps = 0;
    bool isEnd = false;
    MazeObject(int row, int col, Maze *maze);
    /**
         * @brief Function tells if this object is pacman.
         *
         * @return Return true, if this object is pacman.
         */
    bool isPacman();
    /**
         * @brief Function tells if this object is ghost.
         *
         * @return Return true, if this object is ghost.
         */
    bool isGhost();
     /**
         * @brief Function tells if this object is key.
         *
         * @return Return true, if this object is key.
         */
    bool isKey();
    /**
         * @brief Function tells if this object is target.
         *
         * @return Return true, if this object is target.
         */
    bool isTarget();
    /**
         * @brief Sets this object as pacman.
         *
         */
    void setPacman();
    /**
         * @brief Sets this object as ghost.
         *
         */
    void setGhost();
    /**
         * @brief Sets this object as key.
         *
         */
    void setKey();
    /**
         * @brief Sets this object as target.
         *
         */
    void setTarget();
    /**
         * @brief Function tells whether object can move to neighbouring Field.
         *
         * @param dir Direction.
         * @return Returns true if object can move.
         */
    bool canMove(Direction dir);
    /**
         * @brief Moves this object to neighbouring field.
         *
         * @param dir Direction.
         * @return Returns true if object moved successfully.
         */
    bool move(Direction dir);
    /**
         * @brief Damages this object (lowers the number of lives).
         *
         */
    void damage();
    /**
         * @brief Function get the number of lives left.
         *
         * @return Number of lives.
         */
    int get_lives();

    /**
         * @brief Function controls whether pacman picked key.
         *
         * @return Return true, if this object has a key.
         */
    bool hasKey();

     /**
      * @brief Get the row count
      * 
      * @return rows
      */
    int getRows();

     /**
      * @brief Get the col count
      * 
      * @return cols
      */
    int getCols();

    /**
     * @brief Get the number of steps taken
     * 
     * @return steps
     */
    int get_steps();
};

#endif
