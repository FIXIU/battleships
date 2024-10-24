#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>

using namespace std;


class Board
{
private:
    int boardSize;
    vector<vector<char>> privateBoard;
    int numOfShips;
public:
    Board(int size);
    ~Board();
    void printBoard();
    void placeShip(int posX, int posY, bool orientation, int length);
    bool checkForShips(int posX, int posY);
};

#endif