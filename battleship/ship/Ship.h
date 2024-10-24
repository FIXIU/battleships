#ifndef SHIP_H
#define SHIP_H

class Ship
{
private:
    int shipLength;
    int posX;
    int posY;
    bool orientation;
public:
    Ship(int length, int posX, int posY, bool orientation);
    ~Ship();
};

#endif