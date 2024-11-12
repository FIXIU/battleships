#pragma once
#include "Player.h"
#include "../board/Board.h"
#include "../ship/Ship.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

Player::Player(string playerName, int playerScore)
{
    this -> name = playerName;
    this -> score = playerScore;

    for (int i = 3; i >= 0; i--)
    {
        this -> numOfShips[i] = 0; // TODO: change to this -> numOfShips[i] = i+1;
    }
    
}

Player::~Player()
{
}

bool isValidNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int stringToInt(const string& str) {
    int number = 0;
    for (char c : str) {
        number = number * 10 + (c - '0'); // Convert char to int and add to total
    }
    return number;
}

void Player::placeShips(Board& playerBoard)
{
    int choice, posX, posY, length;
    char orientation, Yn;
    string input;
    bool orientationToF = false; // same as orientation just true or false

    if (numOfShips[0] > 0 || numOfShips[1] > 0 || numOfShips[2] > 0 || numOfShips[3] > 0)
    {
        cout << name << " place your ships!" << endl; // TODO: decide if this needs removing (incase we don't want to print this whenever this function is called (as it is recurrent))

        playerBoard.printBoard();

        cout << "Choose one of the following ships to place" << endl;
        cout << "1 mast ship (" << this -> numOfShips[0] << " left)" << endl;
        cout << "2 mast ship (" << this -> numOfShips[1] << " left)" << endl;
        cout << "3 mast ship (" << this -> numOfShips[2] << " left)" << endl;
        cout << "4 mast ship (" << this -> numOfShips[3] << " left)" << endl;
        cout << "Input the ammount of mast ship you'd like to place: ";
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
                cout << "select the X position you'd like to place your ship at: ";
                cin >> posX;
                cout << "select the Y position you'd like to place your ship at: ";
                cin >> posY;

                break;

            case 2:
            case 3:
            case 4:
                cout << "select the X position you'd like to place your ship at: ";
                cin >> input;
                if (isValidNumber(input)) {
                    posX = stringToInt(input);
                }
                else {
                    cout << "Invalid input. Please enter a number." << endl;
                    this_thread::sleep_for(chrono::milliseconds(3000));
                    system("CLS");
                    placeShips(playerBoard);
                }
                cout << "select the Y position you'd like to place your ship at: ";
                cin >> choice;
                if (isValidNumber(input)) {
                    posY = stringToInt(input);
                }
                else {
                    cout << "Invalid input. Please enter a number." << endl;
                    this_thread::sleep_for(chrono::milliseconds(3000));
                    system("CLS");
                    placeShips(playerBoard);
                }
                cout << "select the orientation you'd like your ship to face (N, E, S, W): ";
                cin >> orientation;
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
                cin >> Yn;
                if (Yn != 'Y' && Yn != 'y')
                {
                    playerBoard.unplaceShip(posX-1, posY-1, orientationToF, length);
                }
                else {
                    numOfShips[choice-1] -= 1;
                    ships.push_back(Ship(length, posX-1, posY-1, orientationToF));
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
    for (int i = 3; i >= 0; i--)
    {
        this -> numOfShips[i] = i+1; // TODO: change to this -> numOfShips[i] = i+1;
    }
}

vector<Ship> &Player::getShips()
{
    return this -> ships;
}
