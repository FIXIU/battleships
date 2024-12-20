#pragma once
#include "Menu.h"
#include "../player/Player.cc"
#include <iostream>
#include <cctype>
#include <limits>

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
    cout << "Welcome to Battleships!" << endl;
    cout << "Make your selection:" << endl;
    cout << "1. Play a game of Battleships against another human (hotseat)" << endl;
    cout << "2. Play a game of Battleships against the computer" << endl;
    cout << "3. Credits" << endl;
    cout << "4. Quit" << endl;

    int choice = 0;
    string input;
    
    cout << "\nPick one of the options: ";
    cin >> input;
    cin.clear(); // Resets any error flags on cin (like when invalid input happens)
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear everything until newline
    
    if (isValidNumber(input)) {
        choice = stringToInt(input);
        if (choice < 1 || choice > 5) {
            cout << "Invalid choice. Please try again." << endl;
            this_thread::sleep_for(chrono::milliseconds(3000));
            system("CLS");
            showMenu();
            return;
        }
    }
    else 
    {
        cout << "Invalid input. Please enter a number." << endl;
        this_thread::sleep_for(chrono::milliseconds(3000));
        system("CLS");
        showMenu();
        return;
    }

    switch (choice)
    {
        case 1:
            this -> gameMode = 0;
            cout << "Enter the first player's name: ";
            cin >> this -> playerOneName;
            cout << "Enter the second player's name: ";
            cin >> this -> playerTwoName;
            break;
        case 2:
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
            cout << "please head over to this website -> https://www.youtube.com/watch?v=dQw4w9WgXcQ" << endl;
            this_thread::sleep_for(chrono::milliseconds(5000));
            system("CLS");
            this -> quit = 1;
            break;
    }
    this_thread::sleep_for(chrono::milliseconds(500));
    system("CLS");
}

void Menu::credits()
{
    cout << "This game was created by fixiu" << endl;
    cout << "pssst... input '5' as the choice in the menu" << endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    showMenu();
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
