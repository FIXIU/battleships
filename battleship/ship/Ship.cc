#include "Ship.h"
#include "../board/Board.cc"

#include <iostream>

using namespace std;

Ship::Ship(int length, int posX, int posY, bool orientation)
{
    this -> shipLength = length;
    this -> posX = posX;
    this -> posY = posY;
    this -> orientation = orientation;
}

Ship::~Ship()
{
}
