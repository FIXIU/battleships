#include <iostream>
#include <vector>
#include "board/Board.cc"
#include "menu/Menu.cc"
#include "player/Player.cc"
#include "computer/Computer.cc"

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

int getXCoordinates()
{
    string input;
    int posX;
    bool rightInput = 0;

    cout << "\tX coordinates: ";

    while (rightInput == 0)
    {
        cin >> input;
        if (isValidNumber(input))
        {
            posX = translateInput(input);
            rightInput = 1;
        }
        else {
            cout << "Invalid input. Please enter a number." << endl;
            this_thread::sleep_for(chrono::milliseconds(3000));
            system("CLS");
            return -1;
        }
    }
    return posX;
}

int getYCoordinates()
{
    string input;
    int posY;
    bool rightInput = 0;

    cout << "\tY coordinates: ";

    while (rightInput == 0)
    {
        cin >> input;
        if (isValidNumber(input))
        {
            posY = translateInput(input);
            rightInput = 1;
        }
        else {
            cout << "Invalid input. Please enter a number." << endl;
            this_thread::sleep_for(chrono::milliseconds(3000));
            system("CLS");
            return -1;
        }
    }
    return posY;
    
}

bool playerOneTurn(Board &playerOneBoard, Board &playerTwoBoard, Player &playerOne, Menu &newMenu)
{
    bool hit = 0;
    int posX, posY;
    string input;
    cout << "Your board" << endl;
    playerOneBoard.printBoard();
    cout << newMenu.getPlayerTwoName() << "'s board" << endl;
    playerTwoBoard.printBoardForEnemy();
    cout << "Which cell do you want to shoot?" << endl;
    
    posX = getXCoordinates();
    posY = getYCoordinates();

    if (posX == -1 || posY == -1)
    {
        playerOneTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
    }

    if (posY > playerTwoBoard.getSize() || posX > playerTwoBoard.getSize())
    {
        cout << "You tried to shoot outside of the board! Try again.";
        this_thread::sleep_for(chrono::milliseconds(3000));
        system("CLS");
        playerOneTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
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
        playerOneTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
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

    return hit;
}

bool playerTwoTurn(Board &playerOneBoard, Board &playerTwoBoard, Player &playerOne, Menu &newMenu)
{
    bool hit = 0;
    int posX, posY;
    string input;
    cout << "Your board" << endl;
    playerTwoBoard.printBoard();
    cout << newMenu.getPlayerOneName() << "'s board" << endl;
    playerOneBoard.printBoardForEnemy();
    cout << "Which cell do you want to shoot?" << endl;

    posX = getXCoordinates();
    posY = getYCoordinates();

    if (posX == -1 || posY == -1)
    {
        playerTwoTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
    }


    if (posY > playerOneBoard.getSize() || posX > playerOneBoard.getSize())
    {
        cout << "You tried to shoot outside of the board! Try again.";
        this_thread::sleep_for(chrono::milliseconds(3000));
        system("CLS");
        playerTwoTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
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

    return hit;
}

bool computerTurn(Board &playerOneBoard, Computer &computer, Menu &newMenu)
{
    bool hit = 0 ;
    cout << "Computer's turn!" << endl;
    cout << "Your board:" << endl;
    playerOneBoard.printBoard();
    
    // Get computer's shot
    int posX, posY;
    computer.makeShot(playerOneBoard);
    
    // Process the shot
    if (playerOneBoard.checkForShips(posX, posY) == 1) {
        cout << "Computer hit your ship at position (" << posX+1 << "," << posY+1 << ")!" << endl;
        hit = true;
    } else {
        cout << "Computer missed at position (" << posX+1 << "," << posY+1 << ")!" << endl;
    }
    
    playerOneBoard.shootForEnemy(posX, posY);
    
    this_thread::sleep_for(chrono::milliseconds(2000));
    system("CLS");
    
    return hit;
}

void turn(bool currentPlayer, int turnNumber, bool gameMode, Board &playerOneBoard, Board &playerTwoBoard, Menu &newMenu, Player &playerOne, Player &playerTwo, Computer &computer, Board &computerBoard)
{
    int posX, posY, choice;
    bool hit = 0;
    string input;

    if (newMenu.getGameMode() == false)
    {
        if (currentPlayer == false)
        {
            playerOneTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
        }
        else
        {
            playerTwoTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
        }

        this_thread::sleep_for(chrono::milliseconds(3000));
        system("CLS");
        
        if (playerOneBoard.allShipsSunk() != 1 && playerTwoBoard.allShipsSunk() != 1)
        {
            currentPlayer = (hit) ? currentPlayer : !currentPlayer;

            turnNumber++;
            turn(currentPlayer, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo, computer, computerBoard);
        }

        if (currentPlayer)
        {
            playerTwo.addPlayerScore(1);
        }
        else 
        {
            playerOne.addPlayerScore(1);
        }
    }
    else 
    {
        if (currentPlayer == false) 
        {
            hit = playerOneTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
        } 
        else 
        {
            hit = computerTurn(playerOneBoard, computer, newMenu);
        }

        this_thread::sleep_for(chrono::milliseconds(3000));
        system("CLS");
        
        if (playerOneBoard.allShipsSunk() != 1 && computerBoard.allShipsSunk() != 1)
        {
            currentPlayer = (hit) ? currentPlayer : !currentPlayer;

            turnNumber++;
            turn(currentPlayer, turnNumber, gameMode, playerOneBoard, playerTwoBoard, newMenu, playerOne, playerTwo, computer, computerBoard);
        }

        if (currentPlayer)
        {
            computer.addPlayerScore(1);
        }
        else 
        {
            playerOne.addPlayerScore(1);
        }
    }   

    
    
}

void clearAll(Menu &mainMenu, Player &playerOne, Player &playerTwo, Board &playerOneBoard, Board &playerTwoBoard)
{
    playerOne.clearShips();
    playerTwo.clearShips();

    playerOneBoard.clearBoard();
    playerTwoBoard.clearBoard();
}

void singlePlayer(Menu &mainMenu, Player &playerOne, Player &playerTwo, Board &playerOneBoard, Board &playerTwoBoard, Board &computerBoard, Computer &computer)
{
    int onePreviousScore, computerPreviousScore, winnerScore;
    string winnerName;

    system("CLS");
    
    playerOne.placeShips(playerOneBoard);
    computer.placeShipsRandomly(computerBoard);

    turn(0, 1, 1, playerOneBoard, playerTwoBoard, mainMenu, playerOne, playerTwo, computer, computerBoard);

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
    computerPreviousScore = computer.getScore();

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
            singlePlayer(mainMenu, playerOne, playerTwo, playerOneBoard, playerTwoBoard, computerBoard, computer);
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
}

void multiPlayer(Menu &mainMenu, Player &playerOne, Player &playerTwo, Board &playerOneBoard, Board &playerTwoBoard, Computer &computer, Board &computerBoard)
{
    int onePreviousScore, twoPreviousScore, winnerScore;
    string winnerName;

    system("CLS");

    
    
    playerOne.placeShips(playerOneBoard);
    playerTwo.placeShips(playerTwoBoard);

    turn(0, 1, 0, playerOneBoard, playerTwoBoard, mainMenu, playerOne, playerTwo, computer, computerBoard);

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
            multiPlayer(mainMenu, playerOne, playerTwo, playerOneBoard, playerTwoBoard, computer, computerBoard);
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
//                          TODO: no string int check at the place ships
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
        Computer computer(10); // Sadly I have to create the computer object here
        Board computerBoard(10); // Sadly I have to create the computer board object here

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

        multiPlayer(mainMenu, playerOne, playerTwo, playerOneBoard, playerTwoBoard, computer, computerBoard);
    }
    else {
        Player playerOne(mainMenu.getPlayerOneName(), 0);
        Board playerOneBoard(10);
        Board computerBoard(10);
        Computer computer(10);

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

        playerOne.placeShips(playerOneBoard);

        computer.placeShipsRandomly(computerBoard);

        turn(0, 1, 1, playerOneBoard, computerBoard, mainMenu, playerOne, playerOne, computer, computerBoard);
    
        singlePlayer(mainMenu, playerOne, playerOne, playerOneBoard, computerBoard, computerBoard, computer);
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
