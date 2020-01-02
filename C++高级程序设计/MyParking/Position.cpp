#include "Position.h"
#include<string>
#include<time.h>

Position::Position(){};

Position::Position(int col, int row, int flag) :flag(flag), car(nullptr)
{
    setPos(col, row);
    valid = true;
}

void Position::setPos(int col, int row)
{
    if (col > 0 && row > 0) {
        this->col = col;
        this->row = row;
    }
    else {
        // error()
        col = row = 0;
    }
}

void Position::setInTime(string t)
{
    this->inTime = t;
}

string Position::getInTime()
{
    return this->inTime;
}

void Position::setOutTime(string t)
{
    this->outTime = t;
}

string Position::getOutTime()
{
    return this->outTime;
}

bool Position::isValid(){
    return valid;
}

void Position::setValid(){
    valid = true;
}

void Position::resetValid(){
    valid = false;
}

int Position::getFlag(){
    return flag;
}

