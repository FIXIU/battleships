#ifndef SHIP_H
#define SHIP_H

class Ship
{
private:
    int posX;
    int posY;
    bool orientation;
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
};

#endif