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
    void printBoardForEnemy(); // This prints the board for the enemy (you use the playerOneBoard when you want to print the playerOne's board for playerTwo)
    bool placeShip(int posX, int posY, bool orientation, int length);
    void unplaceShip(int posX, int posY, bool orientation, int length);
    bool checkForShips(int posX, int posY);
    void shootForEnemy(int posX, int posY); // This shoots for the enemy (you use the playerOneBoard when playerTwo shoots)
};

#endif