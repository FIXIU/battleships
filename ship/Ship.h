#ifndef SHIP_H
#define SHIP_H
#include <iostream>
#include <vector>

using namespace std;

class Ship
{
private:
    int posX;
    int posY;
    bool orientation;
    vector<int> position;
public:
    int shipLength;
    Ship(int length, int posX, int posY, bool orientation);
    ~Ship();
    int cellsShot;
    void shootAt(int posX, int posY, bool hit);
    bool isSunk();
    int getPosX();
    int getPosY();
    bool getOrientation();
    void markShipSunk();
};

#endif