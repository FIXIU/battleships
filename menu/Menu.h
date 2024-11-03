#ifndef MENU_H
#define MENU_H

#include <iostream>

using namespace std;

class Menu
{
private:
    string playerOneName;
    string playerTwoName;
    bool gameMode;
public:
    Menu();
    ~Menu();
    void showMenu();
    void credits();
    bool getGameMode();
    string getPlayerOneName();
    string getPlayerTwoName();
};


#endif