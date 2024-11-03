#pragma once
#include "Board.h"
#include "../ship/Ship.cc"
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
                cout << " ~ ";
            } 
            else if (privateBoard[i][j] == 'x')
            {
                cout << " X "; // print the hit
            }
            else if (privateBoard[i][j] == 'm')
            {
                cout << " M "; // print miss
            }
            else {
                cout << " o "; // print the ship 
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

//
//                      TODO: FIX THIS MADNESS (most wanted outcome: the water being colored in the windows cmd) !!!!!!!! THE COLOR MESSES WITH THE COMPILER !!!!!!!
//

        for (int j = 0; j < boardSize; j++) {
            if(privateBoard[i][j] == 'x')
            {
                cout << " X ";
            }
            else if(privateBoard[i][j] == 'm')
            {
                cout << " O ";
            }
            else {
                cout << " ~ ";
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

bool Board::checkForShips(int posX, int posY)
{
    if (privateBoard[posX][posY] == 'o')
    {
        return true;
    }
    else {
        return false;
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
