/**
 * @file Maze.hpp
 * @author Jakub Kořínek <xkorin17@stud.fit.vutbr.cz>
 * @brief Header file defining the whole maze.
 */

#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <cstring>
#include <iostream>
#include "Field.hpp"

/**
 * @class Maze
 * @brief Class representing the whole maze.
 * 
 */
class Maze{
protected:
    /**
         * Maze itself is saved is matrix of pointers, to each pointer you can assign a field.
         *
         */
    Field ***field;
    int rows;
    int cols;
    int current_row;

public:
    /**
         * @brief Function allocates necessary memory and fills the first line with walls.
         *
         * @param rows Required number of rows.
         * @param cols Required number of cols.
         * @return True if successful.
         */
    bool startReading(int rows, int cols);
    /**
         * @brief Function processes new line.
         *
         * @param line String representation of a line.
         * @return True if successful.
         */
    bool processLine(std::string line);
    /**
         * @brief Function ends reading and fill the last row with walls.
         *
         * @return True if successful.
         */
    bool stopReading();
    /**
         * @brief Function creates ready maze.
         *
         * @return Instance of maze.
         */
    Maze createMaze();
    /**
         * @brief Releases allocated memory.
         *
         */
    void clearMaze();
    /**
     * @brief Get the number of rows
     * 
     * @return returns number of rows
     */
    int getRows(){
        return this->rows;
    }
    /**
     * @brief Get the number of cols
     * 
     * @return returns number of cols
     */
    int getCols(){
        return this->cols;
    }
    /**
         * @brief Function loads the adress of particular field.
         *
         * @param row X position
         * @param col Y position
         * @return Returns the adress of a Field[x,y].
         */
    Field* getField(int row, int col);
};

#endif
