#pragma once
#include "Board.h"
#include "../ship/Ship.cc"
#include "../player/Player.cc"
#include <iostream>

using namespace std;


Board::Board(int size) : boardSize(size)
{
    privateBoard.resize(size, vector<char>(size, '.'));
}

Board::~Board()
{
}

void Board::printBoard() {
    // Print the top row with numbers
    cout << " ";
    for (int i = 0; i < boardSize; i++)
    {
        if (i < 9)
        {
            cout << " " << i+1 << " ";
        }
        else
        {
            cout << " " << i+1;
        }
        
        
    }
    cout << endl;
    

    // Print the game grid and number indexes
    for (int i = 0; i < boardSize; i++) {
        char letter = 'a' + i; // set the letter according to the number index
        cout << letter; // print the letter index

        for (int j = 0; j < boardSize; j++) {
            if (privateBoard[i][j] == '.') {
                 // print ~ for empty space (water)
                cout << "\033[34m ~ \033[0m";
            } 
            else if (privateBoard[i][j] == 'x')
            {
                cout << "\033[31m X \033[0m"; // print the hit
            }
            else if (privateBoard[i][j] == 'm')
            {
                cout << "\033[33m M \033[0m"; // print miss
            }
            else {
                cout << "\033[32m o \033[0m"; // print the ship 
            }
        }

        cout << endl;
    }
}

void Board::printBoardForEnemy()
{

    // Print the top row with numbers
    cout << " ";
    for (int i = 0; i < boardSize; i++)
    {
        if (i < 9)
        {
            cout << " " << i+1 << " ";
        }
        else
        {
            cout << " " << i+1;
        }
        
        
    }
    cout << endl;
    

    // Print the game grid and number indexes
    for (int i = 0; i < boardSize; i++) {
        char letter = 'a' + i; // set the letter according to the number index
        cout << letter; // print the letter index

        for (int j = 0; j < boardSize; j++) {
            if(privateBoard[i][j] == 'x')
            {
                cout << "\033[31m X \033[0m";
            }
            else if(privateBoard[i][j] == 'm' || privateBoard[i][j] == '#')
            {
                cout << "\033[33m M \033[0m";
            }
            else {
                cout << "\033[34m ~ \033[0m";
            }
        }

        cout << endl;
    } 
}

bool Board::placeShip(int posX, int posY, bool orientation, int length) {
    // Check if the ship can be placed at the given position
    if (orientation) { // Horizontal orientation
        if (posY + length > boardSize) {
            cout << "Error: Ship cannot be placed at the given position." << endl;
            return false;
        }
        for (int i = posY; i < posY + length; i++) {
            // Check cell itself
            if (privateBoard[posX][i] != '.') {
                cout << "Error: Ship cannot be placed at the given position." << endl;
                return false;
            }
            // Check adjacent cells
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    // Skip the cell itself
                    if (dx == 0 && dy == 0) continue;

                    int checkX = posX + dx;
                    int checkY = i + dy;

                    // Check if the adjacent cell is within the board boundaries
                    if (checkX >= 0 && checkX < boardSize && checkY >= 0 && checkY < boardSize) {
                        if (privateBoard[checkX][checkY] != '.') {
                            cout << "Error: Ship cannot be placed at the given position." << endl;
                            return false;
                        }
                    }
                }
            }
        }
        // Place the ship
        for (int i = posY; i < posY + length; i++) {
            privateBoard[posX][i] = 'o'; 
        }
        Ship newShip(length, posX, posY, orientation);
        ships.push_back(newShip);
        return true;
    } else { // Vertical orientation
        if (posX + length > boardSize) {
            cout << "Error: Ship cannot be placed at the given position." << endl;
            return false;
        }
        for (int i = posX; i < posX + length; i++) {
            // Check cell itself
            if (privateBoard[i][posY] != '.') {
                cout << "Error: Ship cannot be placed at the given position." << endl;
                return false;
            }

            // Check adjacent cells
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    // Skip the cell itself
                    if (dx == 0 && dy == 0) continue;

                    int checkX = i + dx;
                    int checkY = posY + dy;

                    // Check if the adjacent cell is within the board boundaries
                    if (checkX >= 0 && checkX < boardSize && checkY >= 0 && checkY < boardSize) {
                        if (privateBoard[checkX][checkY] != '.') {
                            cout << "Error: Ship cannot be placed at the given position." << endl;
                            return false;
                        }
                    }
                }
            }
        }
        // Place the ship
        for (int i = posX; i < posX + length; i++) {
            privateBoard[i][posY] = 'o'; 
        }
        Ship newShip(length, posX, posY, orientation);
        ships.push_back(newShip);

        return true;
    }
}

void Board::unplaceShip(int posX, int posY, bool orientation, int length)
{
    if (orientation) { // Horizontal orientation
        // Place the water tile
        for (int i = posY; i < posY + length; i++) {
            privateBoard[posX][i] = '.';
        }
    } else { // Vertical orientation
        // Place water tile
        for (int i = posX; i < posX + length; i++) {
            privateBoard[i][posY] = '.';
        }
    }
}

int Board::checkForShips(int posX, int posY)
{
    if (privateBoard[posX][posY] == 'o')
    {
        return 1;
    }
    else if (privateBoard[posX][posY] == 'x' || privateBoard[posX][posY] == 'm' || privateBoard[posX][posY] == '#')
    {
        return 2;
    }
    else {
        return 3;
    }
}

void Board::shootForEnemy(int posX, int posY)
{
    if (privateBoard[posX][posY] == 'o')
    {
        privateBoard[posX][posY] = 'x'; // Mark the cell as hit
        for (Ship& ship : ships) {
            if (isPositionPartOfShip(ship, posX, posY)) {
                ship.shootAt(posX, posY, true);
                if (ship.isSunk()) {
                    markSunkShip(ship.getPosX(), ship.getPosY(), ship.getOrientation(), ship.shipLength);
                    markAroundSunkShip(ship.getPosX(), ship.getPosY(), ship.getOrientation(), ship.shipLength);
                }
                break;
            }
        }
    }
    else if (privateBoard[posX][posY] == '.' || privateBoard[posX][posY] == '#') {
        privateBoard[posX][posY] = 'm'; // Mark the cell as missed
    }
}

bool Board::isPositionPartOfShip(const Ship& ship, int posX, int posY) {
    int shipX = ship.getPosX();
    int shipY = ship.getPosY();
    bool orientation = ship.getOrientation();
    
    if (orientation) { // horizontal
        return posX == shipX && posY >= shipY && posY < shipY + ship.shipLength;
    } else { // vertical
        return posY == shipY && posX >= shipX && posX < shipX + ship.shipLength;
    }
}

bool Board::allShipsSunk()
{
    for (int i = 0; i < this -> boardSize; i++)
    {
        for (int j = 0; j < this -> boardSize; j++)
        {
            if (this -> privateBoard[i][j] == 'o')
            {
                return 0;
            }
        }
    }
    return 1;
}

int Board::getSize()
{
    return this -> boardSize;
}

void Board::clearBoard()
{
    for (int i = 0; i < this -> boardSize; i++)
    {
        for (int j = 0; j < this -> boardSize; j++)
        {
            privateBoard[i][j] = '.';
        } 
    }
    
}

void Board::markSunkShip(int posX, int posY, bool orientation, int length) {
    if (orientation) { // Horizontal
        for (int i = posY; i < posY + length; i++) {
            privateBoard[posX][i] = 'x';
        }
    } else { // Vertical
        for (int i = posX; i < posX + length; i++) {
            privateBoard[i][posY] = 'x';
        }
    }
}

void Board::markAroundSunkShip(int posX, int posY, bool orientation, int length) {
    if (orientation) { // Horizontal
        // Mark cells above and below
        for (int i = posY - 1; i <= posY + length; i++) {
            if (i >= 0 && i < boardSize) {
                if (posX - 1 >= 0 && privateBoard[posX-1][i] == '.') 
                    privateBoard[posX-1][i] = '#';
                if (posX + 1 < boardSize && privateBoard[posX+1][i] == '.')
                    privateBoard[posX+1][i] = '#';
            }
        }
        // Mark cells at the ends
        if (posY - 1 >= 0 && privateBoard[posX][posY-1] == '.')
            privateBoard[posX][posY-1] = '#';
        if (posY + length < boardSize && privateBoard[posX][posY+length] == '.')
            privateBoard[posX][posY+length] = '#';
    } else { // Vertical
        // Mark cells to the left and right
        for (int i = posX - 1; i <= posX + length; i++) {
            if (i >= 0 && i < boardSize) {
                if (posY - 1 >= 0 && privateBoard[i][posY-1] == '.')
                    privateBoard[i][posY-1] = '#';
                if (posY + 1 < boardSize && privateBoard[i][posY+1] == '.')
                    privateBoard[i][posY+1] = '#';
            }
        }
        // Mark cells at the ends
        if (posX - 1 >= 0 && privateBoard[posX-1][posY] == '.')
            privateBoard[posX-1][posY] = '#';
        if (posX + length < boardSize && privateBoard[posX+length][posY] == '.')
            privateBoard[posX+length][posY] = '#';
    }
}

