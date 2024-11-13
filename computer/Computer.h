#ifndef COMPUTER_H
#define COMPUTER_H
#include "../board/Board.cc"
#include <vector>
#include <cstdlib> // random
#include <ctime>

using namespace std;

class Computer {
private:
    vector<vector<bool>> shotGrid;
    int lastHitX;
    int lastHitY;
    bool huntMode;                  // True when hunting a ship (when a ship is hit and we are searching for the rest of it)
    int boardSize;
    int computerScore;

public:
    Computer(int size);
    ~Computer();
    void makeShot(Board& enemyBoard);
    void placeShipsRandomly(Board& board);
    void addPlayerScore(int score);
    bool isValidShot(int x, int y);
    void getRandomShot(int& x, int& y);
    void getAdjacentShot(int& x, int& y);
    int getScore();
    int getLastHitX();
    int getLastHitY();
};

#endif