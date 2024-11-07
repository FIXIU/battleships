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

int translateInput(string input)
{
    if (isValidNumber(input)) {
        return stringToInt(input);
    }
    else {
        return -1;
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

void turn(bool currentPlayer, int turnNumber, bool gameMode, Board &playerOneBoard, Board &playerTwoBoard, Menu &newMenu, Player &playerOne, Player &playerTwo)
{
    int posX, posY;
    bool hit;
    int choice;
    string input;

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
            cin >> input;
            

            if (isValidNumber(input))
            {
                posX = translateInput(input);
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                this_thread::sleep_for(chrono::milliseconds(3000));
                system("CLS");
                turn(false, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo);
            }
            
    
            
            cout << "\tY coordinates: ";
            cin >> input;

            if (isValidNumber(input))
            {
                posY = translateInput(input);
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                this_thread::sleep_for(chrono::milliseconds(3000));
                system("CLS");
                turn(false, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo);
            }

            if (posY > playerTwoBoard.getSize() || posX > playerTwoBoard.getSize())
            {
                cout << "You tried to shoot outside of the board! Try again.";
                this_thread::sleep_for(chrono::milliseconds(3000));
                system("CLS");
                turn(false, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo);
            }

            if (playerTwoBoard.checkForShips(posX-1, posY-1) == 3)
            {
                cout << "You've missed!" << endl;
                hit = 0;
            }
            else if (playerTwoBoard.checkForShips(posX-1, posY-1) == 2)
            {
                cout << "You can't shoot a cell you've already shot at! Try again!" << endl;
                this_thread::sleep_for(chrono::milliseconds(3000));
                system("CLS");
                turn(currentPlayer, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo);
                return;
                hit = 0;
            }
            else {
                cout << "You've hit a ship!";
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
            cin >> input;
            if (isValidNumber(input))
            {
                posX = translateInput(input);
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                this_thread::sleep_for(chrono::milliseconds(3000));
                system("CLS");
                turn(false, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo);
            }
            cout << "\tY coordinates: ";
            cin >> input;
            if (isValidNumber(input))
            {
                posY = translateInput(input);
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                this_thread::sleep_for(chrono::milliseconds(3000));
                system("CLS");
                turn(false, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo);
            }

            if (posY > playerOneBoard.getSize() || posX > playerOneBoard.getSize())
            {
                cout << "You tried to shoot outside of the board! Try again.";
                this_thread::sleep_for(chrono::milliseconds(3000));
                system("CLS");
                turn(false, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo);
            }


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
            cin >> input;
            if (isValidNumber(input))
            {
                posX = translateInput(input);
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                this_thread::sleep_for(chrono::milliseconds(3000));
                system("CLS");
                turn(false, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo);
            }
            cout << "\tY coordinates: ";
            cin >> input;
            if (isValidNumber(input))
            {
                posY = translateInput(input);
            }
            else {
                cout << "Invalid input. Please enter a number." << endl;
                this_thread::sleep_for(chrono::milliseconds(3000));
                system("CLS");
                turn(false, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo);
            }

            if (posY > playerTwoBoard.getSize() || posX > playerTwoBoard.getSize())
            {
                cout << "You tried to shoot outside of the board! Try again.";
                this_thread::sleep_for(chrono::milliseconds(3000));
                system("CLS");
                turn(false, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo);
            }
            

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
    
    if (playerOneBoard.allShipsSunk() != 1 && playerTwoBoard.allShipsSunk() != 1)
    {
        /*
        I've figured this is the excact same thing as it was earlier, just simpler (note for future self)
        if (!hit)
        {
            currentPlayer = !currentPlayer;
        }
        */
        currentPlayer = (hit) ? currentPlayer : !currentPlayer;

        turnNumber++;
        turn(currentPlayer, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo);
    }

    if (currentPlayer)
    {
        playerTwo.addPlayerScore(1);
    }
    else {
        playerOne.addPlayerScore(1);
    }
    
}

void clearAll(Menu &mainMenu, Player &playerOne, Player &playerTwo, Board &playerOneBoard, Board &playerTwoBoard)
{
    playerOne.clearShips();
    playerTwo.clearShips();

    playerOneBoard.clearBoard();
    playerTwoBoard.clearBoard();
}

void multiPlayer(Menu &mainMenu, Player &playerOne, Player &playerTwo, Board &playerOneBoard, Board &playerTwoBoard)
{
    int onePreviousScore, twoPreviousScore, winnerScore;
    string winnerName;

    system("CLS");

    
    
    playerOne.placeShips(playerOneBoard);
    playerTwo.placeShips(playerTwoBoard);

    turn(0, 1, 0, playerOneBoard, playerTwoBoard, mainMenu, playerOne, playerTwo);

    char Yn;

    if (onePreviousScore < playerOne.getScore())
    {
        winnerName = playerOne.getName();
        winnerScore = playerOne.getScore();
    }
    else {
        winnerName = playerTwo.getName();
        winnerScore = playerTwo.getScore();
    }
    
    

    cout << "Congratulations " << winnerName << " you have won this game!" << endl;
    cout << "Your score is now: " << winnerScore + 1;

    this_thread::sleep_for(chrono::milliseconds(3000));
    
    bool f = 0;

    onePreviousScore = playerOne.getScore();
    twoPreviousScore = playerTwo.getScore();

    while (f == 0)
    {
        system("CLS");

        cout << playerOne.getName() << " score: " << playerOne.getScore() << endl;
        cout << playerTwo.getName() << " score: " << playerTwo.getScore() << endl;

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> Yn;

        clearAll(mainMenu, playerOne, playerTwo, playerOneBoard, playerTwoBoard);

        if (Yn == 'Y' || Yn == 'y')
        {
            multiPlayer(mainMenu, playerOne, playerTwo, playerOneBoard, playerTwoBoard);
            f = 1;
        }
        else if (Yn == 'N' || Yn == 'n')
        {
            f = 1;
        }
        else {
            cout << "Invalid input. Please enter Y or N.";
            this_thread::sleep_for(chrono::milliseconds(2000));
        }
    }
    system("CLS");
//
//
//a
//                          TODO: https://calendar.google.com/calendar/u/0/r/tasks
//                          TODO: ADD THE COMPUTER
//                          TODO: maybe add a thingy that says "give the seat to the other player and asks for input when they've changed"
//a
//
//
}

void game(Menu &mainMenu)
{
    mainMenu.showMenu();
    
    if (mainMenu.quit)
    {
        return;
    }

    
    if (!mainMenu.getGameMode())
    {
        // Creating the player objects
        Player playerOne(mainMenu.getPlayerOneName(), 0);
        Player playerTwo(mainMenu.getPlayerTwoName(), 0);
        // Creating the board objects
        Board playerOneBoard(10);
        Board playerTwoBoard(10);

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



        playerTwoBoard.shootForEnemy(1-1, 3-1);

        playerTwoBoard.shootForEnemy(1-1, 5-1);

        playerTwoBoard.shootForEnemy(1-1, 7-1);
        

        playerTwoBoard.shootForEnemy(1-1, 9-1);
        playerTwoBoard.shootForEnemy(1-1, 10-1);

        playerTwoBoard.shootForEnemy(3-1, 1-1);
        playerTwoBoard.shootForEnemy(3-1, 2-1);
        
        playerTwoBoard.shootForEnemy(3-1, 4-1);
        playerTwoBoard.shootForEnemy(3-1, 5-1);


        playerTwoBoard.shootForEnemy(5-1, 1-1);
        playerTwoBoard.shootForEnemy(5-1, 2-1);
        playerTwoBoard.shootForEnemy(5-1, 3-1);

        playerTwoBoard.shootForEnemy(5-1, 5-1);
        playerTwoBoard.shootForEnemy(5-1, 6-1);
        playerTwoBoard.shootForEnemy(5-1, 7-1);
        

        playerTwoBoard.shootForEnemy(3-1, 7-1);
        playerTwoBoard.shootForEnemy(3-1, 8-1);
        playerTwoBoard.shootForEnemy(3-1, 9-1);
        playerTwoBoard.shootForEnemy(3-1, 10-1);

        multiPlayer(mainMenu, playerOne, playerTwo, playerOneBoard, playerTwoBoard);
    }
    else {
        //TODO: Single player (vs computer)
    }
    
    game(mainMenu);
}

int main()
{
    Menu mainMenu;

    game(mainMenu);


    return 0;

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
