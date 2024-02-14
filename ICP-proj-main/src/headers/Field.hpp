/**
 * @file Field.hpp
 * @author Jakub Kořínek <xkorin17@stud.fit.vutbr.cz>
 * @brief Header file defining class Field and enum class Direction.
 *
 */

#ifndef FIELD_H
#define FIELD_H

class Field;
/**
 * @class Direction
 * @brief Enum class defining usable directions. 
 * 
 */
enum class Direction{
    D,
    L,
    R,
    U,
    None
};

#include "MazeObject.hpp"
#include "Maze.hpp"

/**
 * @class Field
 * @brief A class defining a field in maze.
 * 
 */
class Field{
protected:
    int row;
    int col;
    Maze *maze;


public:
    bool move;
    MazeObject *pacman;
    MazeObject *ghost;
    MazeObject *key;
    MazeObject *target;

    Field(int row, int col, Maze *maze);
    /**
         * @brief Sets field as path.
         *
         */
    void setPath();
    /**
         * @brief THis function makes a difference between wall and path.
         *
         * @return Returns true if this is a path. False otherwise.
         */
    bool canMove();
    /**
         * @brief Finds out whether this field is empty.
         *
         * @return Returns true if field has no object on it.
         */
    bool isEmpty();
    /**
         * @brief Function assigns object to this field..
         *
         * @param object MazeObject.
         * @return If put is successful, return true. False otherwise.
         */
    bool put(MazeObject *object);
    /**
         * @brief Removes object from field.
         *
         * @param object MazeObject.
         * @return Return true if remove is successful. False otherwise.
         */
    bool remove(MazeObject *object);
    /**
         * @brief Function gets adress of Mazeobject on this field.
         *
         * @return Returns the adress of first MazeObject.
         */
    MazeObject* get();
    /**
         * @brief Returns adress of neighbouring field.
         *
         * @param dir Direction.
         * @return Returns the adress of neighbouring field.
         */
    Field* nextField(Direction dir);

     /**
      * @brief Get the ghost object.
      * 
      * @return Return true if it gets ghost successfully.
      */
    bool getGhost();
};

#endif
