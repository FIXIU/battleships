#include "Computer.h"

Computer::Computer(int size) {
    boardSize = size;
    huntMode = 0;
    lastHitX = -1;
    lastHitY = -1;
    
    srand(time(0));
    
    shotGrid.resize(size, vector<bool>(size, 0));
}

Computer::~Computer() {}

bool Computer::isValidShot(int x, int y) {
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return false;
    }
    return !shotGrid[x][y];
}

void Computer::getRandomShot(int& x, int& y) {
    bool canShot = 0;
    do {
        x = rand() % boardSize;
        y = rand() % boardSize;
        canShot = isValidShot(x, y) && ((x + y) % 2 == 0);
    } while (!canShot);
}

void Computer::getAdjacentShot(int& x, int& y) {
    int directions[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    vector<int> availableDirs;
    
    for (int dir = 0; dir < 4; dir++) {
        int newX = lastHitX + directions[dir][0];
        int newY = lastHitY + directions[dir][1];
        
        if (newX >= 0 && newX < boardSize && newY >= 0 && newY < boardSize && !shotGrid[newX][newY]) {
            availableDirs.push_back(dir);
        }
    }
    
    if (availableDirs.empty()) {
        getRandomShot(x, y);
        huntMode = false;
        return;
    }
    
    int chosenDir = availableDirs[rand() % availableDirs.size()];
    x = lastHitX + directions[chosenDir][0];
    y = lastHitY + directions[chosenDir][1];
}

void Computer::makeShot(Board& enemyBoard) {
    int x, y;
    
    if (huntMode) {
        getAdjacentShot(x, y);
    } else {
        getRandomShot(x, y);
    }
    
    // Store the coordinates for reference
    lastHitX = x;
    lastHitY = y;
    
    // Mark this position as shot
    shotGrid[x][y] = true;
    
    // Take the shot and process the result
    bool isHit = (enemyBoard.checkForShips(x, y) == 1);
    enemyBoard.shootForEnemy(x, y);

    char posXChar = 'a' + x;
    if (isHit) {
        huntMode = true;
        cout << "Computer hit your ship at position (" << posXChar << "," << y+1 << ")!" << endl;
    } else {
        huntMode = false;
        cout << "Computer missed at position (" << posXChar << "," << y+1 << ")." << endl;
    }
}

void Computer::placeShipsRandomly(Board& board) {
    board.setSilentMode(true);  // Turn off error messages
    
    int ships[] = {1, 2, 3, 4};
    
    for (int length = 4; length >= 1; length--) {
        for (int i = 0; i < ships[4-length]; i++) {
            bool placed = false;
            while (!placed) {
                int x = rand() % board.getSize();
                int y = rand() % board.getSize();
                bool orientation = rand() % 2;
                
                if (board.placeShip(x, y, orientation, length)) {
                    placed = true;
                }
            }
        }
    }
    
    board.setSilentMode(false);
}

void Computer::addPlayerScore(int score) {
    this -> computerScore += score;
}

int Computer::getScore() {
    return this -> computerScore;
}

int Computer::getLastHitX()
{
    return this -> lastHitX;
}

int Computer::getLastHitY()
{
    return this -> lastHitY;
}

