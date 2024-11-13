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
    int numOfShips[4]; 
public:
    Player(string playerName, int playerScore);
    ~Player();
    void placeShips(Board &playerBoard);
    string getName();
    void addPlayerScore(int score);
    int getScore();
    void clearShips();
};

#endif