#include "Board.h"
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
            } else {
                cout << " o "; // print the ship 
            }
        }

        cout << endl;
    }
}

void Board::placeShip(int posX, int posY, bool orientation, int length)
{
    // Check if the ship can be placed at the given position
    if (orientation) { // Horizontal orientation
        if (posY + length > boardSize) {
            cout << "Error: Ship cannot be placed at the given position." << endl;
            return;
        }
        for (int i = posY; i < posY + length; i++) {
            if (privateBoard[posX][i] != '.') {
                cout << "Error: Ship cannot be placed at the given position." << endl;
                return;
            }
            // Check adjacent cells
            if (posX > 0 && privateBoard[posX - 1][i] != '.') {
                cout << "Error: Ship cannot be placed at the given position." << endl;
                return;
            }
            if (posX < boardSize - 1 && privateBoard[posX + 1][i] != '.') {
                cout << "Error: Ship cannot be placed at the given position." << endl;
                return;
            }

//                      TEST

            if (privateBoard[posX + 1][i - 1] != '.' || privateBoard[posX - 1][i - 1] != '.' || privateBoard[posX + 1][i + 1] != '.' || privateBoard[posX - 1][i + 1] != '.') {
                cout << "Error: Ship cannot be placed at the given position." << endl;
                return;
            }
        }
        // Place the ship
        for (int i = posY; i < posY + length; i++) {
            privateBoard[posX][i] = 'x'; // Use 'x' to represent the ship
        }
    } else { // Vertical orientation
        if (posX + length > boardSize) {
            cout << "Error: Ship cannot be placed at the given position." << endl;
            return;
        }
        for (int i = posX; i < posX + length; i++) {
            if (privateBoard[i][posY] != '.') {
                cout << "Error: Ship cannot be placed at the given position." << endl;
                return;
            }
            // Check adjacent cells
            if (posY > 0 && privateBoard[i][posY - 1] != '.') {
                cout << "Error: Ship cannot be placed at the given position." << endl;
                return;
            }
            if (posY < boardSize - 1 && privateBoard[i][posY + 1] != '.') {
                cout << "Error: Ship cannot be placed at the given position." << endl;
                return;
            }

        }
        // Place the ship
        for (int i = posX; i < posX + length; i++) {
            privateBoard[i][posY] = 'x'; // Use 'x' to represent the ship
        }
    }
}

bool Board::checkForShips(int posX, int posY)
{
    if (privateBoard[posX][posY] == 'x')
    {
        return true;
    }
    else {
        return false;
    }
    
}
