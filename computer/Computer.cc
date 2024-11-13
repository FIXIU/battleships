#include "Computer.h"

Computer::Computer(int size) {
    boardSize = size;
    huntMode = 0;
    lastHitX = -1;
    lastHitY = -1;
    
    // Initialize random seed
    srand(time(0));
    
    // Initialize shot grid with false (no shots taken)
    shotGrid.resize(size, vector<bool>(size, 0));
}

Computer::~Computer() {}

bool Computer::isValidShot(int x, int y) {
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return false;
    }
    return !shotGrid[x][y];  // Return true if we haven't shot here before
}

void Computer::getRandomShot(int& x, int& y) {
    bool canShot = 0;
    do {
        x = rand() % boardSize;
        y = rand() % boardSize;
        // Only allow shots on checkerboard pattern
        canShot = isValidShot(x, y) && ((x + y) % 2 == 0);
    } while (!canShot);
}

void Computer::getAdjacentShot(int& x, int& y) {
    // Only try cardinal directions (no diagonals)
    int directions[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    vector<int> availableDirs;
    
    // Check which directions are valid
    for (int dir = 0; dir < 4; dir++) {
        int newX = lastHitX + directions[dir][0];
        int newY = lastHitY + directions[dir][1];
        
        if (newX >= 0 && newX < boardSize && newY >= 0 && newY < boardSize && !shotGrid[newX][newY]) {
            availableDirs.push_back(dir);
        }
    }
    
    // If no valid directions, get random shot and disable hunt mode
    if (availableDirs.empty()) {
        getRandomShot(x, y);
        huntMode = false;
        return;
    }
    
    // Pick a random valid direction
    int chosenDir = availableDirs[rand() % availableDirs.size()];
    x = lastHitX + directions[chosenDir][0];
    y = lastHitY + directions[chosenDir][1];
}

void Computer::makeShot(Board& enemyBoard) {
    int x, y;
    
    // Decide where to shoot
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
    
    // Update hunting status and display result

    char posXChar = 'a' + x;
    if (isHit) {
        huntMode = true;
        cout << "Computer hit your ship at position (" << posXChar << "," << y+1 << ")!" << endl;
    } else {
        huntMode = false;  // Reset hunt mode on miss
        cout << "Computer missed at position (" << posXChar << "," << y+1 << ")." << endl;
    }
}

void Computer::placeShipsRandomly(Board& board) {
    board.setSilentMode(true);  // Turn off error messages
    
    int ships[] = {1, 2, 3, 4};  // Number of ships of each length
    
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
    
    board.setSilentMode(false);  // Turn error messages back on
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

