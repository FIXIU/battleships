#include <iostream>
#include <vector>
#include "board/Board.cc"
#include "menu/Menu.cc"

using namespace std;

void createBoards(bool gameMode, Board &playerOneBoard, Board &playerTwoBoard)
{
    if (gameMode == 0)
    {
        playerOneBoard = Board(10);
        playerTwoBoard = Board(10);
    }
    else {
        playerOneBoard = Board(10);
        // Assuming computerBoard is not needed to be returned
    }
}

int main()
{
    Board playerOneBoard(10);
    Board playerTwoBoard(10);
    bool currentPlayer = 0;

    // Board newBoard(10);
    // newBoard.printBoard();
    // newBoard.placeShip(5/* the number the user gives + 1 */, 3/* the number the user gives + 1 */, true, 3);
    // newBoard.placeShip(4/* the number the user gives + 1 (posY)*/, 6/* the number the user gives + 1 (posX) */, true, 3);
    // newBoard.placeShip(3/* the number the user gives + 1 (posY)*/, 3/* the number the user gives + 1 (posX) */, true, 3);
    // newBoard.printBoard();

    Menu newMenu("player1", "player2");
    newMenu.showMenu();

    bool gameMode = newMenu.checkGameMode();


    createBoards(gameMode, playerOneBoard, playerTwoBoard);
    
    playerOneBoard.printBoard();

    system("PAUSE");
}
