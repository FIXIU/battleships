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
    }
}


bool processShot(Board &targetBoard, int posX, int posY) {
    if (targetBoard.checkForShips(posX-1, posY-1) == 3) {
        cout << "You've missed!" << endl;
        return false;
    }
    else if (targetBoard.checkForShips(posX-1, posY-1) == 2) {
        cout << "You can't shoot a cell you've already shot at! Try again!" << endl;
        return true;
    }
    else {
        cout << "You've hit a ship!" << endl;
        return true;
    }
}

bool validateShot(int posX, int posY, Board &targetBoard) {
    if (posX == -1 || posY == -1) {
        return false;
    }
    if (posY > targetBoard.getSize() || posX > targetBoard.getSize()) {
        cout << "You tried to shoot outside of the board! Try again.";
        this_thread::sleep_for(chrono::milliseconds(3000));
        system("CLS");
        return false;
    }
    return true;
}

void displayBoards(Board &playerBoard, Board &enemyBoard, string enemyName, bool isPlayerOne) {
    cout << "Your board" << endl;
    playerBoard.printBoard();
    cout << enemyName << "'s board" << endl;
    enemyBoard.printBoardForEnemy();
}

bool playerOneTurn(Board &playerOneBoard, Board &playerTwoBoard, Player &playerOne, Menu &newMenu)
{
    displayBoards(playerOneBoard, playerTwoBoard, newMenu.getPlayerTwoName(), true);
    cout << "Which cell do you want to shoot?" << endl;
    
    int posX = getXCoordinates();
    int posY = getYCoordinates();

    if (!validateShot(posX, posY, playerTwoBoard)) {
        return playerOneTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
    }

    bool hit = processShot(playerTwoBoard, posX, posY);
    
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

    if (playerOneBoard.checkForShips(posX-1, posY-1) == 3)
    {
        cout << "You've missed!" << endl;
        hit = 0;
    }
    else if (playerOneBoard.checkForShips(posX-1, posY-1) == 2)
    {
        cout << "You can't shoot a cell you've already shot at! Try again!" << endl;
        this_thread::sleep_for(chrono::milliseconds(3000));
        system("CLS");
        playerTwoTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
        hit = 0;
    }
    else {
        cout << "You've hit a ship!";
        hit = 1;
    }

    this_thread::sleep_for(chrono::milliseconds(1000));
    system("CLS");

    playerOneBoard.shootForEnemy(posX-1, posY-1);
    cout << "Here's the updated board:" << endl;
    playerOneBoard.printBoardForEnemy();

    return hit;
}

bool computerTurn(Board &playerOneBoard, Computer &computer, Menu &newMenu) {
    bool hit = false;
    computer.makeShot(playerOneBoard);
    
    if (playerOneBoard.checkForShips(computer.getLastHitX(), computer.getLastHitY()) == 1) {
        hit = true;
        this_thread::sleep_for(chrono::milliseconds(1000));
        if (!playerOneBoard.allShipsSunk()) {
            return computerTurn(playerOneBoard, computer, newMenu); // next turn
        }
    }
    
    return hit;
}

void handleGameEnd(bool currentPlayer, Player &playerOne, Player &playerTwo, Computer &computer) {
    if (currentPlayer) {
        if (playerTwo.getName() != "")  // this basically checks if there is a second player
        {
            playerTwo.addPlayerScore(1);
        } 
        else 
        {
            computer.addPlayerScore(1);
        }
    } 
    else 
    {
        playerOne.addPlayerScore(1);
    }
}

bool handlePlayerTurn(bool currentPlayer, Board &playerOneBoard, Board &playerTwoBoard, 
                     Player &playerOne, Menu &newMenu, Computer &computer) {
    if (currentPlayer == false) {
        return playerOneTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
    } else {
        if (newMenu.getGameMode()) {
            return computerTurn(playerOneBoard, computer, newMenu);
        } else {
            return playerTwoTurn(playerOneBoard, playerTwoBoard, playerOne, newMenu);
        }
    }
}

void turn(bool currentPlayer, int turnNumber, bool gameMode, Board &playerOneBoard, 
         Board &playerTwoBoard, Menu &newMenu, Player &playerOne, Player &playerTwo, 
         Computer &computer, Board &computerBoard)
{
    bool hit = handlePlayerTurn(currentPlayer, playerOneBoard, playerTwoBoard, 
                              playerOne, newMenu, computer);

    this_thread::sleep_for(chrono::milliseconds(3000));
    system("CLS");
    
    Board &targetBoard = gameMode ? computerBoard : playerTwoBoard;
    
    if (playerOneBoard.allShipsSunk() != 1 && targetBoard.allShipsSunk() != 1) {
        currentPlayer = (hit) ? currentPlayer : !currentPlayer;
        turnNumber++;
        if (!hit)
        {
            swapSeats();
        }
        turn(currentPlayer, turnNumber, gameMode, playerOneBoard, playerTwoBoard, 
             newMenu, playerOne, playerTwo, computer, computerBoard);
    }

    handleGameEnd(currentPlayer, playerOne, playerTwo, computer);
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
    int onePreviousScore = playerOne.getScore();
    int computerPreviousScore = computer.getScore();
    int winnerScore;
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
    cout << "Your score is now: " << winnerScore;

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
    swapSeats();
    playerTwo.placeShips(playerTwoBoard);
    swapSeats();

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
}

void displayScores(Player &playerOne, Player &playerTwo) {
    cout << playerOne.getName() << " score: " << playerOne.getScore() << endl;
    cout << playerTwo.getName() << " score: " << playerTwo.getScore() << endl;
}

bool getPlayAgainInput() {
    string input;
    cout << "\nDo you want to play again? (Y/N): ";
    cin >> input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (input.length() == 1) {
        char choice = tolower(input[0]);
        if (choice == 'y') return true;
        if (choice == 'n') return false;
    }
    
    cout << "Invalid input. Please enter Y or N.";
    this_thread::sleep_for(chrono::milliseconds(2000));
    return getPlayAgainInput();
}

void handlePlayAgain(Menu &mainMenu, Player &playerOne, Player &playerTwo, 
                    Board &playerOneBoard, Board &playerTwoBoard, 
                    Board &computerBoard, Computer &computer, bool isSinglePlayer) {
    bool playAgain = getPlayAgainInput();
    
    if (playAgain) {
        clearAll(mainMenu, playerOne, playerTwo, playerOneBoard, playerTwoBoard);
        if (isSinglePlayer) {
            singlePlayer(mainMenu, playerOne, playerTwo, playerOneBoard, 
                       playerTwoBoard, computerBoard, computer);
        } else {
            multiPlayer(mainMenu, playerOne, playerTwo, playerOneBoard, 
                      playerTwoBoard, computer, computerBoard);
        }
    }
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

    system("PAUSE");
}
