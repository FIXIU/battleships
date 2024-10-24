#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

using namespace std;

class Player
{
private:
    string playerName;
public:
    Player(string playerName);
    ~Player();
};

#endif