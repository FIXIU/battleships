#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "../ship/Ship.cc"

using namespace std;


class Board
{
private:
    int boardSize;
    vector<vector<char>> privateBoard;
    int numOfShips;
    vector<Ship> ships;
    bool isPositionPartOfShip(const Ship& ship, int posX, int posY);
    bool silentMode = false;
    bool canPlaceShip(int posX, int posY, bool orientation, int length, string &errorMessage);
public:
    Board(int size);
    ~Board();
    void printBoard();
    void printBoardForEnemy(); // This prints the board for the enemy (you use the playerOneBoard when you want to print the playerOne's board for playerTwo)
    bool placeShip(int posX, int posY, bool orientation, int length);
    void unplaceShip(int posX, int posY, bool orientation, int length);
    int checkForShips(int posX, int posY);
    void shootForEnemy(int posX, int posY); // This shoots for the enemy (you use the playerOneBoard when playerTwo shoots)
    bool allShipsSunk();
    int getSize();
    void clearBoard();
    void markSunkShip(int posX, int posY, bool orientation, int length);
    void markAroundSunkShip(int posX, int posY, bool orientation, int length);
    void setSilentMode(bool mode);
    bool getSilentMode();
};

#endif