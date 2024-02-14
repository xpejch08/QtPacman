/**
 * @file Field.cpp
 * @author Jakub Kořínek xkorin17@stud.fit.vutbr.cz
 * @brief Implementation of a field in maze.
 */

#include "../headers/Field.hpp"
#include "../headers/Maze.hpp"

Field::Field(int row, int col, Maze *maze){
    this->row = row;
    this->col = col;
    this->maze = maze;
    this->move = false;
    this->ghost = nullptr;
    this->pacman = nullptr;
    this->key = nullptr;
    this->target = nullptr;
}

void Field::setPath(){
    this->move = true;
}

bool Field::canMove(){
    return this->move && (this->ghost == nullptr || this->pacman == nullptr);
}

bool Field::isEmpty(){
    return (this->ghost == nullptr && this->pacman == nullptr && this->key == nullptr && this->target == nullptr);
}

bool Field::put(MazeObject *object){
    if (this->canMove()){
        if (object->isPacman()){
            this->pacman = object;
            return true;
        }
        if (object->isGhost()){
            this->ghost = object;
            return true;
        }
        if (object->isKey()){
            this->key = object;
            return true;
        }
        if (object->isTarget()){
            this->target = object;
            return true;
        }
    }
    return false;
}

bool Field::remove(MazeObject *object){
    if (object->isPacman()){
        this->pacman = nullptr;
        return true;
    }
    if (object->isGhost()){
        this->ghost = nullptr;
        return true;
    }
    if (object->isKey()){
        this->key = nullptr;
        return true;
    }
    if (object->isTarget()){
        this->target = nullptr;
        return true;
    }
    return false;
}

MazeObject* Field::get(){
    if (this->pacman != nullptr)
        return this->pacman;
    if (this->ghost != nullptr)
        return this->ghost;
    if (this->key != nullptr)
        return this->key;
    if (this->target != nullptr)
        return this->target;
    return nullptr;
}

Field* Field::nextField(Direction dir){
    switch (dir){
    case Direction::D: return (*this->maze).getField(this->row+1, this->col);
    case Direction::R: return (*this->maze).getField(this->row, this->col+1);
    case Direction::L: return (*this->maze).getField(this->row, this->col-1);
    case Direction::U: return (*this->maze).getField(this->row-1, this->col);
    default:
        throw "neexistující políčko";
    }
}

bool Field::getGhost()
{
    if(this->ghost != nullptr){
        return true;
    }
    return false;
}
