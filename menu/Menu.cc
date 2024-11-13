#pragma once
#include "Menu.h"
#include "../player/Player.cc"
#include <iostream>
#include <cctype>

using namespace std;


Menu::Menu()
{
    this -> quit = 0;
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
    string input;
    
    cout << "\nPick one of the options: ";
    cin >> input;
    
    if (isValidNumber(input)) {
            choice = stringToInt(input);
    }

    switch (choice)
    {
        case 1:
            // TODO: HOTSEAT!!!
            this -> gameMode = 0;
            cout << "Enter the first player's name: ";
            cin >> this -> playerOneName;
            cout << "Enter the second player's name: ";
            cin >> this -> playerTwoName;
            break;
        case 2:
            // TODO: VS COMPUTER!!!!
            this -> gameMode = 1;
            cout << "Enter the player's name: ";
            cin >> this -> playerOneName;
            break;
        case 3:
            credits();
            break;
        case 4:
            this -> quit = 1;
            break;
        case 5:
            cout << "w9DNf3GH2US@Js7 https://www.youtube.com/watch?v=dQw4w9WgXcQ" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            
            this_thread::sleep_for(chrono::milliseconds(3000));
            system("CLS");

            showMenu();
            break;
    }
    this_thread::sleep_for(chrono::milliseconds(500));
    system("CLS");
}

void Menu::credits()
{
    cout << "This game was created by fixiu" << endl;
    cout << "dsadasdas" << endl;
    cout << "pssst... input w9DNf3GH2US@Js7 at the choice in the menu" << endl; // TODO: REMOVE THIS
}

bool Menu::getGameMode()
{
    return this -> gameMode;
}

string Menu::getPlayerOneName()
{
    return this -> playerOneName;
}

string Menu::getPlayerTwoName()
{
    return this -> playerTwoName;
}
