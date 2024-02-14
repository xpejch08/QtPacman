/**
 * @file Maze.cpp
 * @author Jakub Kořínek <xkorin17@stud.fit.vutbr.cz>
 * @brief Implementation of maze class.
 */

#include "../headers/MazeObject.hpp"
#include "../headers/Field.hpp"
#include "../headers/Maze.hpp"

bool Maze::startReading(int rows, int cols){
    this->rows = rows+2;
    this->cols = cols+2;
    this->current_row = 1;

    try{
        this->field = new Field**[this->rows];
        for (int i = 0; i < this->rows; ++i)
            this->field[i] = new Field*[this->cols];

        for (int i = 0; i < this->cols; i++)
            this->field[0][i] = new Field(0, i, this);
    }
    catch (std::exception& e){
        std::cerr << "Chyba: " << e.what() << std::endl;
        return false;
    }

    return true;
}

bool Maze::processLine(std::string line){
    const int lenght = line.length();
    if (lenght != this->cols-2){
        return false;
    }
    char *parsed_line = new char[lenght+1];
    strcpy(parsed_line, line.c_str());
    MazeObject *ghost;
    MazeObject *pacman;
    MazeObject *key;
    MazeObject *target;

    this->field[this->current_row][0] = new Field(this->current_row, 0, this);
    for (int i = 1; i < lenght+1; i++){
        switch(parsed_line[i-1]){
        // prázdná cesta
        case '.':
            this->field[this->current_row][i] = new Field(this->current_row, i, this);
            this->field[this->current_row][i]->setPath();
            break;
        // zeď
        case 'X':
            this->field[this->current_row][i] = new Field(this->current_row, i, this);
            break;
        // cesta s duchem
        case 'G':
            this->field[this->current_row][i] = new Field(this->current_row, i, this);
            this->field[this->current_row][i]->setPath();
            ghost = new MazeObject(this->current_row, i, this);
            ghost->setGhost();
            this->field[this->current_row][i]->put(ghost);
            break;
        // cesta s pacmanem
        case 'S':
            this->field[this->current_row][i] = new Field(this->current_row, i, this);
            this->field[this->current_row][i]->setPath();
            pacman = new MazeObject(this->current_row, i, this);
            pacman->setPacman();
            this->field[this->current_row][i]->put(pacman);
            break;
        // cesta s cílem
        case 'T':
            this->field[this->current_row][i] = new Field(this->current_row, i, this);
            this->field[this->current_row][i]->setPath();
            target = new MazeObject(this->current_row, i, this);
            target->setTarget();
            this->field[this->current_row][i]->put(target);
            break;
        // cesta s klíčem
        case 'K':
            this->field[this->current_row][i] = new Field(this->current_row, i, this);
            this->field[this->current_row][i]->setPath();
            key = new MazeObject(this->current_row, i, this);
            key->setKey();
            this->field[this->current_row][i]->put(key);
            break;
        default:
            std::cerr << "Neznámé políčko na pozici [" << this->current_row << "," << i <<"]\n";
            return false;
        }
    }
    this->field[this->current_row][this->cols-1] = new Field(this->current_row, 0, this);
    this->current_row++;

    delete parsed_line;

    return true;
}

bool Maze::stopReading(){
    for (int i = 0; i < this->cols; i++){
        this->field[this->rows-1][i] = new Field(this->rows-1, i, this);
    }
    return true;
}

Maze Maze::createMaze(){
    return *this;
}

void Maze::clearMaze(){
    for (int i = 0; i < this->rows; ++i){
        for (int j = 0; j < this->cols; ++j){
            delete [] this->field[i][j];
        }
        delete [] this->field[i];
    }
    delete [] this->field;
}

Field* Maze::getField(int row, int col){
    return this->field[row][col];
}
