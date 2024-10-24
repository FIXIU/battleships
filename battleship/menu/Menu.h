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
    Menu(string playerOneName, string playerTwoName);
    ~Menu();
    void showMenu();
    void credits();
    bool checkGameMode();
};


#endif