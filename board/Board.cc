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

//
//                      TODO: FIX THIS MADNESS (most wanted outcome: the water being colored in the windows cmd) !!!!!!!! THE COLOR MESSES WITH THE COMPILER !!!!!!!
//

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
            else if (privateBoard[i][j] == '#')
            {
                cout << " # ";
            }
            else {
                cout << "\033[32m o \033[0m"; // print the ship 
            }
        }

        cout << endl;
    }
}

void Board::printBoardForEnemy(Player &currentPlayer)
{
    markSunkShips(currentPlayer); // mark all sunk ships before the board prints for enemy
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

//
//                      TODO: FIX THIS MADNESS (most wanted outcome: the water being colored in the windows cmd) !!!!!!!! THE COLOR MESSES WITH THE COMPILER !!!!!!!
//

        for (int j = 0; j < boardSize; j++) {
            if(privateBoard[i][j] == 'x')
            {
                cout << "\033[31m X \033[0m";
            }
            else if(privateBoard[i][j] == 'm')
            {
                cout << "\033[33m M \033[0m";
            }
            else if (privateBoard[i][j] == '#')
            {
                cout << "\033[32m # \033[0m";
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
            for (int dx = -1; dx <= 1; dx++) { //changed from ++dx
                for (int dy = -1; dy <= 1; dy++) { // --||--
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
        privateBoard[posX][posY] = 'x'; // Mark the cell as hit (ship)
    }
    else {
        privateBoard[posX][posY] = 'm'; // Mark the cell as missed
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

void Board::markSunkShips(Player &player) {
    vector<Ship> ships = player.getShips();
    for (Ship &ship : ships) {
        if (ship.isSunk()) {
            // Get ship's coordinates
            int startX = ship.getPosX();
            int startY = ship.getPosY();
            bool orientation = ship.getOrientation();

            // Mark the ship itself with '#'
            for (int i = 0; i < ship.shipLength; ++i) {
                if (orientation) {
                    privateBoard[startX][startY + i] = '#';
                } else {
                    privateBoard[startX + i][startY] = '#';
                }
            }

            // Mark surrounding cells with '#'
            for (int i = startX - 1; i <= startX + 1; ++i) {
                for (int j = startY - 1; j <= startY + ship.shipLength; ++j) {
                    if (i >= 0 && i < boardSize && j >= 0 && j < boardSize) {
                        if (privateBoard[i][j] != 'o' && privateBoard[i][j] != 'x' && privateBoard[i][j] != 'm' && privateBoard[i][j] != '#') {
                            privateBoard[i][j] = '#';
                        }
                    }
                }
            }
        }
    }
}
