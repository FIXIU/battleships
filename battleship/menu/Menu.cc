#include "Menu.h"
#include <iostream>

using namespace std;


Menu::Menu(string playerOneName, string playerTwoName)
{
    this -> playerOneName = playerOneName;
    this -> playerTwoName = playerTwoName;
}

Menu::~Menu()
{
}

void Menu::showMenu()
{
    cout << "Welcome to Battleships!" << endl; // TODO: input some fancy ass ASCII art here
    cout << "Make your selection:" << endl;
    cout << "1. Play a game of Battleships against another human (hotseat)" << endl;
    cout << "2. Play a game of Battleships against the computer" << endl;
    cout << "3. Credits" << endl;
    cout << "4. Quit" << endl;

    int choice;
    
    cout << "\nPick one of the options: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
            // TODO: HOTSEAT!!!
            this -> gameMode = 0;
            break;
        case 2:
            // TODO: VS COMPUTER!!!!
            this -> gameMode = 1;
            break;
        case 3:
            credits();
            break;
        case 4:
            // TODO: QUIT!!
            break;
        case 5:
            cout << "Stack overflow didn't help... just paste this link into your browser... https://www.youtube.com/watch?v=dQw4w9WgXcQ" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

void Menu::credits()
{
    cout << "This game was created by fixiu" << endl;
    cout << "dsadasdas" << endl;
    cout << "pssst... input \'5\' into the selection menu at the start :D" << endl;
}

bool Menu::checkGameMode()
{
    return this -> gameMode;
}
