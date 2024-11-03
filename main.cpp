#include <iostream>
#include <vector>
#include "board/Board.cc"
#include "menu/Menu.cc"
#include "player/Player.cc"

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

void createPlayers(bool gameMode, Player &playerOne, Player &playerTwo, Menu &menu)
{
    if (gameMode == 0)
    {
        playerOne = Player(menu.getPlayerOneName(), 0);
        playerTwo = Player(menu.getPlayerTwoName(), 0);
    }
    else {
        playerOne = Player(menu.getPlayerOneName(), 0);
        // Assuming computerPlayer is not needed to be returned
    }
}

void turn(bool currentPlayer, int turnNumber, bool gameMode, Board &playerOneBoard, Board &playerTwoBoard, Menu &newMenu)
{
    int posX, posY;
    bool hit;

    if (newMenu.getGameMode() == false)
    {
        if (currentPlayer == false)
        {
            // Player 1's turn
            cout << "Your board" << endl;
            playerOneBoard.printBoard();
            cout << newMenu.getPlayerTwoName() << "'s board" << endl;
            playerTwoBoard.printBoardForEnemy();
            cout << "Which cell do you want to shoot?" << endl;
            cout << "\tX coordinates: ";
            cin >> posX;
            cout << "\tY coordinates: ";
            cin >> posY;
            if (playerTwoBoard.checkForShips(posX-1, posY-1) == false)
            {
                cout << "You've missed!" << endl;
                hit = 0;
            }
            else {
                cout << "You've hit a ship!" << endl;
                hit = 1;
            }

            this_thread::sleep_for(chrono::milliseconds(1000));
            system("CLS");

            playerTwoBoard.shootForEnemy(posX-1, posY-1);
            cout << "Here's the updated board:" << endl;
            playerTwoBoard.printBoardForEnemy();
        }
        else
        {
            // Player 2's turn
            cout << "Your board" << endl;
            playerTwoBoard.printBoard();
            cout << newMenu.getPlayerOneName() << "'s board" << endl;
            playerOneBoard.printBoardForEnemy();
            cout << "Which cell do you want to shoot?" << endl;
            cout << "\tX coordinates: ";
            cin >> posX;
            cout << "\tY coordinates: ";
            cin >> posY;
            if (playerOneBoard.checkForShips(posX-1, posY-1) == false)
            {
                cout << "You've missed!" << endl;
            }
            else {
                cout << "You've hit a ship!" << endl;
            }

            this_thread::sleep_for(chrono::milliseconds(1000));
            system("CLS");

            playerOneBoard.shootForEnemy(posX-1, posY-1);
            cout << "Here's the updated board:" << endl;
            playerOneBoard.printBoardForEnemy();
        }
    }
    else 
    {
        // Player's turn TODO: FIX THIS TO WORK WITH THE COMPUTER !IMPORTANT! there's a playerTwoBoard object used, we don't want that
            cout << "Your board" << endl;
            playerOneBoard.printBoard();
            cout << newMenu.getPlayerTwoName() << "'s board" << endl;
            playerTwoBoard.printBoardForEnemy();
                    cout << "Which cell do you want to shoot?" << endl;
            cout << "\tX coordinates: ";
            cin >> posX;
            cout << "\tY coordinates: ";
            cin >> posY;
            if (playerTwoBoard.checkForShips(posX-1, posY-1) == false)
            {
                cout << "You've missed!" << endl;
                hit = 0;
            }
            else {
                cout << "You've hit a ship!" << endl;
                hit = 1;
            }

            this_thread::sleep_for(chrono::milliseconds(1000));
            system("CLS");

            playerTwoBoard.shootForEnemy(posX-1, posY-1);
            cout << "Here's the updated board:" << endl;
            playerTwoBoard.printBoardForEnemy();
    }   

    this_thread::sleep_for(chrono::milliseconds(3000));
    system("CLS");
    
    /*
    I've figured this is the excact same thing as it was earlier, just simpler (note for future self)
    if (!hit)
    {
        currentPlayer = !currentPlayer;
    }
    */
    currentPlayer = (hit) ? currentPlayer : !currentPlayer;

    turnNumber++;
    turn(currentPlayer, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu);
}

void multiPlayer(Menu &mainMenu, Player &playerOne, Player &playerTwo, Board &playerOneBoard, Board &playerTwoBoard)
{
    playerOneBoard.placeShip(1-1, 1-1, 1, 1);
    playerOneBoard.placeShip(1-1, 3-1, 1, 1);
    playerOneBoard.placeShip(1-1, 5-1, 1, 1);
    playerOneBoard.placeShip(1-1, 7-1, 1, 1);
    
    playerOneBoard.placeShip(1-1, 9-1, 1, 2);
    playerOneBoard.placeShip(3-1, 1-1, 1, 2);
    playerOneBoard.placeShip(3-1, 4-1, 1, 2);

    playerOneBoard.placeShip(5-1, 1-1, 1, 3);
    playerOneBoard.placeShip(5-1, 5-1, 1, 3);
    
    playerOneBoard.placeShip(3-1, 7-1, 1, 4);


    playerTwoBoard.placeShip(1-1, 1-1, 1, 1);
    playerTwoBoard.placeShip(1-1, 3-1, 1, 1);
    playerTwoBoard.placeShip(1-1, 5-1, 1, 1);
    playerTwoBoard.placeShip(1-1, 7-1, 1, 1);
    
    playerTwoBoard.placeShip(1-1, 9-1, 1, 2);
    playerTwoBoard.placeShip(3-1, 1-1, 1, 2);
    playerTwoBoard.placeShip(3-1, 4-1, 1, 2);

    playerTwoBoard.placeShip(5-1, 1-1, 1, 3);
    playerTwoBoard.placeShip(5-1, 5-1, 1, 3);
    
    playerTwoBoard.placeShip(3-1, 7-1, 1, 4);
    
    playerOne.placeShips(playerOneBoard);
    playerTwo.placeShips(playerTwoBoard);

    turn(0, 0, 0, playerOneBoard, playerTwoBoard, mainMenu);

//
//
//a
//                          TODO: https://calendar.google.com/calendar/u/0/r/tasks
//                          TODO: ADD COLORS AND FINISH THE GAME (ADD A CHECK FOR IF ALL THE SHIPS HAVE BEEN SUNK)
//                          TODO: maybe add a thingy that says "give the seat to the other player and asks for input when they've changed"
//a
//
//
}

void game(Menu &mainMenu)
{
    mainMenu.showMenu();
    // Creating the player objects

    // Creating the board objects

    
    if (!mainMenu.getGameMode())
    {
        // Creating the player objects
        Player playerOne(mainMenu.getPlayerOneName(), 0);
        Player playerTwo(mainMenu.getPlayerTwoName(), 0);
        // Creating the board objects
        Board playerOneBoard(10);
        Board playerTwoBoard(10);

        multiPlayer(mainMenu, playerOne, playerTwo, playerOneBoard, playerTwoBoard);
    }
    else {
        //TODO: Single player (vs computer)
    }
    

}

int main()
{
    Menu mainMenu;

    game(mainMenu);


    // Board playerOneBoard(10);
    // Board playerTwoBoard(10);
    // bool currentPlayer = 0;

    // // Board newBoard(10);
    // // newBoard.printBoard();
    // // newBoard.placeShip(5/* the number the user gives + 1 */, 3/* the number the user gives + 1 */, true, 3);
    // // newBoard.placeShip(4/* the number the user gives + 1 (posY)*/, 6/* the number the user gives + 1 (posX) */, true, 3);
    // // newBoard.placeShip(3/* the number the user gives + 1 (posY)*/, 3/* the number the user gives + 1 (posX) */, true, 3);
    // // newBoard.printBoard();

    // Menu newMenu;
    // newMenu.showMenu();

    // bool gameMode = newMenu.getGameMode();

    // Player playerOne(newMenu.getPlayerOneName(), 0);
    // Player playerTwo(newMenu.getPlayerTwoName(), 0);

    // createBoards(gameMode, playerOneBoard, playerTwoBoard);
    // createPlayers(gameMode, playerOne, playerTwo, newMenu);

    
    // playerOne.placeShips(playerOneBoard);


    system("PAUSE");
}
