#include <iostream>
#include <vector>
#include "board/Board.cc"

using namespace std;

int main()
{
    Board newBoard(10);
    newBoard.printBoard();
    newBoard.placeShip(5/* the number the user gives + 1 */, 3/* the number the user gives + 1 */, true, 3);
    newBoard.placeShip(4/* the number the user gives + 1 (posY)*/, 6/* the number the user gives + 1 (posX) */, true, 3);
    newBoard.placeShip(3/* the number the user gives + 1 (posY)*/, 3/* the number the user gives + 1 (posX) */, true, 3);
    newBoard.printBoard();

    system("PAUSE");
}
