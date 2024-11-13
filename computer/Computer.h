#ifndef COMPUTER_H
#define COMPUTER_H
#include "../board/Board.cc"
#include <vector>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

using namespace std;

class Computer {
private:
    vector<vector<bool>> shotGrid;  // Tracks where computer has shot
    int lastHitX;                   // Stores last successful hit X
    int lastHitY;                   // Stores last successful hit Y
    bool huntMode;                  // True when hunting a ship
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