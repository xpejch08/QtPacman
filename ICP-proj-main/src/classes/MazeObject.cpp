/**
 * @file MazeObject.cpp
 * @author Jakub Kořínek xkorin17@stud.fit.vutbr.cz
 * @brief This file implements MazeObject class.
 */

#include "../headers/MazeObject.hpp"

MazeObject::MazeObject(int row, int col, Maze *maze){
    this->row = row;
    this->col = col;
    this->maze = maze;
    this->ghost = false;
    this->pacman = false;
    this->key = false;
    this->target = false;
    this->lives = 3;
    this->ownsKey = false;
    this->startRow = row;
    this->startCol = col;
}

bool MazeObject::isPacman(){
    return this->pacman;
}

bool MazeObject::isGhost(){
    return this->ghost;
}

bool MazeObject::isKey(){
    return this->key;
}

bool MazeObject::isTarget(){
    return this->target;
}

void MazeObject::setPacman(){
    this->pacman = true;
}

void MazeObject::setGhost(){
    this->ghost = true;
}

void MazeObject::setKey(){
    this->key = true;
}

void MazeObject::setTarget(){
    this->target = true;
}

bool MazeObject::canMove(Direction dir){
    switch (dir){
    case Direction::D:
        return (*this->maze).getField(this->row+1, this->col)->canMove();
        break;
    case Direction::L:
        return (*this->maze).getField(this->row, this->col-1)->canMove();
        break;
    case Direction::R:
        return (*this->maze).getField(this->row, this->col+1)->canMove();
        break;
    case Direction::U:
        return (*this->maze).getField(this->row-1, this->col)->canMove();
        break;
    default:
        return false;
    }
}

bool MazeObject::move(Direction dir){
    if (canMove(dir)){
        Field *nextField = (*this->maze).getField(this->row, this->col)->nextField(dir);
        Field *thisField = (*this->maze).getField(this->row,this->col);
        // tento blok se spustí jen pokud je v cílovém poli nějaký objekt
        if (!nextField->isEmpty()){
            MazeObject *nextObject = nextField->get();
            // tento objekt je Pacman ...
            if (this->isPacman()){
                //... a v cíli je Ghost -> uber život
                if (nextObject->isGhost()){
                    this->damage();
                    this->row = this->startRow;
                    this->col = this->startCol;
                    Field *start = this->maze->getField(row, col);
                    start->put(this);
                    thisField->remove(this);
                    return true;
                }
                //... a v cíli je klíč -> zruš klíč a dej ho Pacmanovi
                else if (nextObject->isKey()){
                    this->ownsKey = true;
                    nextField->remove(nextObject);
                    // úklid v paměti
                    delete nextObject;
                }
                //... a v cíli je cíl -> jestli nemáš klíč, nesmíš jít, jinak konec hry
                else if (nextObject->isTarget()){
                    if (this->hasKey()){
                        this->isEnd = true;
                        nextField->remove(nextObject);
                        // úklid v paměti
                        delete nextObject;
                    }
                    else{
                        return false;
                    }
                }

            }
            // tento objekt je duch ...
            else if (this->isGhost()){
                //... a v cíli je Pacman -> uber život
                if (nextObject->isPacman()){
                    nextObject->damage();
                    nextObject->row = nextObject->startRow;
                    nextObject->col = nextObject->startCol;
                    Field *start = nextObject->maze->getField(row, col);
                    start->put(this);
                    nextField->remove(nextObject);
                    return true;
                }
                //... a v cíli je jiný objekt -> zůstaň stát (ukonči move() s false)
                else
                    return false;
            }
        }
        // přesun
        nextField->put(this);
        thisField->remove(this);
        //přepsání souřadnic objektu
        switch (dir){
        case Direction::D:
            this->row++;
            break;
        case Direction::L:
            this->col--;
            break;
        case Direction::R:
            this->col++;
            break;
        case Direction::U:
            this->row--;
            break;
        }
        return true;
    }
    return false;
}

void MazeObject::damage(){
    this->lives--;
}

int MazeObject::get_lives(){
    return this->lives;
}

bool MazeObject::hasKey(){
    return this->ownsKey;
}

int MazeObject::getRows()
{
    return this->row;
}
int MazeObject::getCols()
{
    return this->col;
}
int MazeObject::get_steps(){
    return this->steps;
}
