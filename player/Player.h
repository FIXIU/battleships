#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "../board/Board.cc"

using namespace std;

class Player
{
private:
    string name;
    int score;
    //int numOfShips[4]{4, 3, 2, 1}; // This array stores the ammount of n-mast ships left (i = 0 - 1 mast ship, i = 1 - 2 mast ship, ...) TODO: uncomment
    int numOfShips[4]{0, 0, 0, 0}; // TODO: comment
public:
    Player(string playerName, int playerScore);
    ~Player();
    void placeShips(Board &playerBoard);
};

#endif