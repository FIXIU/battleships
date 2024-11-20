#pragma once
#include "Player.h"
#include "../board/Board.cc"
#include <iostream>
#include <chrono>
#include <thread>
#include <limits>

using namespace std;

Player::Player(string playerName, int playerScore)
{
    this -> name = playerName;
    this -> score = playerScore;

    for (int i = 0; i < 4; i++)
    {
        this -> numOfShips[i] = 0;//4-i; TODO: change back to 4-i
    }
    
}

Player::~Player()
{
}

int stringToInt(const string& str) {
    int number = 0;
    for (char c : str) {
        number = number * 10 + (c - '0'); // Convert char to int and add to total
    }
    return number;
}

bool isValidNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int translateInput(string input)
{
    if (isValidNumber(input)) {
        return stringToInt(input);
    }
    else {
        return -1;
    }
}

void swapSeats()
{
    cout << "Press enter to swap seats." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    system("CLS");
}

int getXCoordinates()
{
    string input;
    int posX;

    cout << "\tRow (a-j): ";
    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (input.length() == 1) {
        if (isalpha(input[0])) {
            char inputChar = tolower(input[0]);
            if (inputChar >= 'a' && inputChar <= 'j') {
                posX = inputChar - 'a' + 1;
                return posX;
            }
        } else if (isdigit(input[0])) {
            int num = input[0] - '0';
            if (num >= 1 && num <= 10) {
                return num;
            }
        }
    }
    
    cout << "Invalid input. Please enter a letter between a and j or number between 1-10." << endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    system("CLS");
    return getXCoordinates();
}

int getYCoordinates()
{
    string input;
    int posY;

    cout << "\tColumn (1-10): ";
    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (input.length() == 1) {
        if (isalpha(input[0])) {
            char inputChar = tolower(input[0]);
            if (inputChar >= 'a' && inputChar <= 'j') {
                posY = inputChar - 'a' + 1;
                return posY;
            }
        } else if (isdigit(input[0])) {
            int num = input[0] - '0';
            if (num >= 1 && num <= 10) {
                return num;
            }
        }
    }
    
    cout << "IInvalid input. Please enter a letter between a and j or number between 1-10." << endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    system("CLS");
    return getYCoordinates();
}

void getOrientation(char& orientation) {
    string input;
    cout << "\tOrientation (N, E, S, W): ";
    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (input.length() == 1) {
        orientation = tolower(input[0]);
        if (orientation != 'n' && orientation != 'e' && 
            orientation != 's' && orientation != 'w') {
            cout << "Invalid orientation. Please try again." << endl;
            this_thread::sleep_for(chrono::milliseconds(3000));
            getOrientation(orientation);
        }
    } else {
        cout << "Invalid input. Please enter a single character." << endl;
        this_thread::sleep_for(chrono::milliseconds(3000));
        getOrientation(orientation);
    }
}

void Player::placeShips(Board& playerBoard)
{
    int choice, posX, posY, length;
    char orientation, Yn;
    string input;
    bool orientationToF = false; // same as orientation just true or false

    if (numOfShips[0] > 0 || numOfShips[1] > 0 || numOfShips[2] > 0 || numOfShips[3] > 0)
    {
        cout << name << " place your ships!" << endl;

        playerBoard.printBoard();

        cout << "Choose one of the following ships to place" << endl;
        cout << "1 mast ship (" << this -> numOfShips[0] << " left)" << endl;
        cout << "2 mast ship (" << this -> numOfShips[1] << " left)" << endl;
        cout << "3 mast ship (" << this -> numOfShips[2] << " left)" << endl;
        cout << "4 mast ship (" << this -> numOfShips[3] << " left)" << endl;
        cout << "Input the length of the ship you'd like to place: ";
        cin >> input;
        
        if (isValidNumber(input)) {
            choice = stringToInt(input);
        }
        else {
            cout << "Invalid input. Please enter a number." << endl;
            this_thread::sleep_for(chrono::milliseconds(3000));
            system("CLS");
            placeShips(playerBoard);
        }

        length = choice; // that's the same thing. I chose to add a length variable for clarity

        if (this -> numOfShips[choice-1] != 0)
        {
            switch (choice)
            {
            case 1:
                cout << "Place your ship: " << endl;
                posX = getXCoordinates();
                posY = getYCoordinates();

                break;

            case 2:
            case 3:
            case 4:
                cout << "Place your ship: " << endl;
                posX = getXCoordinates();
                posY = getYCoordinates();
                getOrientation(orientation);
                if (orientation == 'N' || orientation == 'n')
                {
                    orientationToF = 0;
                    posX -= length-1;
                }
                else if(orientation == 'E' || orientation == 'e')
                {
                    orientationToF = 1;
                }
                else if(orientation == 'S' || orientation == 's')
                {
                    orientationToF = 0;
                }
                else if(orientation == 'W' || orientation == 'w')
                {
                    orientationToF = 1;
                    posY -= length-1;
                }
                else {
                    cout << "Invalid orientation. Please try again." << endl;
                    this_thread::sleep_for(chrono::milliseconds(3000));
                }

                break;

            default:
                cout << "Invalid ship choice. Please try again." << endl;
                this_thread::sleep_for(chrono::milliseconds(3000));
                system("CLS");
                placeShips(playerBoard);
                break;
            }
            system("CLS");
            if (playerBoard.placeShip(posX-1, posY-1, orientationToF, length))
            {
                playerBoard.printBoard();

                cout << "Is this where you wanted to place your ship? (Y/n)";
                cin >> input;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (input.length() == 1) {
                    char Yn = tolower(input[0]);
                    if (Yn != 'y') {
                        playerBoard.unplaceShip(posX-1, posY-1, orientationToF, length);
                    } else {
                        numOfShips[choice-1] -= 1;
                    }
                } else {
                    playerBoard.unplaceShip(posX-1, posY-1, orientationToF, length);
                }
            }
            else {
                this_thread::sleep_for(chrono::milliseconds(3000));
            }
        }
        else {
            cout << "You cannot place that ship since there's none left!" << endl;
            this_thread::sleep_for(chrono::milliseconds(3000));
        }
        system("CLS");
        placeShips(playerBoard);
    }
    else {
        cout << "You have placed all your ships!" << endl;
        this_thread::sleep_for(chrono::milliseconds(3000));
        system("CLS");
    }
}

string Player::getName()
{
    return this -> name;
}

void Player::addPlayerScore(int score)
{
    this -> score += score;
}

int Player::getScore()
{
    return this -> score;
}

void Player::clearShips()
{
    for (int i = 0; i < 4; i++)
    {
        this -> numOfShips[i] = 4-i;
    }
}
