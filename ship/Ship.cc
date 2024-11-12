#pragma once
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
    this -> cellsShot = 0;
    if (orientation)
    {
        for (int i = posY; i < posY + length; i++) {
            this -> position.push_back(i);
        }
    } else {
        for (int i = posX; i < posX + length; i++) {
            this -> position.push_back(i);
        }
    }
}

Ship::~Ship()
{
}

void Ship::shootAt(int posX, int posY, bool hit)
{
    if (hit)
    {
        this -> cellsShot++;
    }
}

bool Ship::isSunk()
{
    if (this -> cellsShot >= this -> shipLength)
    {
        return 1;
    }
    else {
        return 0;
    }
}

int Ship::getPosX()
{
    return this -> posX;
}

int Ship::getPosY()
{
    return this -> posY;
}

bool Ship::getOrientation()
{
    return this -> orientation;
}

void Ship::markShipSunk()
{
}
