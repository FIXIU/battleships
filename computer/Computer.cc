#include "Computer.h"

Computer::Computer(int size) {
    boardSize = size;
    huntMode = false;
    lastHitX = -1;
    lastHitY = -1;
    
    // Initialize random seed
    srand(time(0));
    
    // Initialize shot grid with false (no shots taken)
    shotGrid.resize(size, vector<bool>(size, false));
}

Computer::~Computer() {}

bool Computer::isValidShot(int x, int y) {
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) {
        return false;
    }
    return !shotGrid[x][y];  // Return true if we haven't shot here before
}

void Computer::getRandomShot(int& x, int& y) {
    do {
        x = rand() % boardSize;
        y = rand() % boardSize;
    } while (!isValidShot(x, y));
}

void Computer::getAdjacentShot(int& x, int& y) {
    // Try up, right, down, left from last hit
    int directions[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    
    // Try 10 times to find a valid adjacent shot
    for (int tries = 0; tries < 10; tries++) {
        int dir = rand() % 4;  // Random direction 0-3
        x = lastHitX + directions[dir][0];
        y = lastHitY + directions[dir][1];
        
        if (isValidShot(x, y)) {
            return;
        }
    }
    
    // If we couldn't find an adjacent shot, just get a random one
    getRandomShot(x, y);
}

void Computer::makeShot(Board& enemyBoard) {
    int x, y;
    
    // Decide where to shoot
    if (huntMode) {
        getAdjacentShot(x, y);
    } else {
        getRandomShot(x, y);
    }
    
    // Mark this position as shot
    shotGrid[x][y] = true;
    
    // Take the shot and process the result
    bool isHit = (enemyBoard.checkForShips(x, y) == 1);
    enemyBoard.shootForEnemy(x, y);
    
    // Update hunting status
    if (isHit) {
        huntMode = true;
        lastHitX = x;
        lastHitY = y;
        cout << "Computer hit your ship at position (" << x+1 << "," << y+1 << ")!" << endl;
    } else {
        cout << "Computer missed at position (" << x+1 << "," << y+1 << ")." << endl;
    }
}

void Computer::placeShipsRandomly(Board& board) {
    int ships[] = {1, 2, 3, 4};  // Number of ships: [4-mast, 3-mast, 2-mast, 1-mast]
    
    for (int length = 4; length >= 1; length--) {
        for (int i = 0; i < ships[4-length]; i++) {
            bool placed = 0;
            while (!placed) {
                int x = rand() % board.getSize();
                int y = rand() % board.getSize();
                bool orientation = rand() % 2;  // 0 for vertical, 1 for horizontal
                
                if (board.placeShip(x, y, orientation, length)) { //TODO: THE COMPUTER PRINTS 1, 69 idk why fix this plz
                    placed = 1;
                }
            }
        }
    }
}

void Computer::addPlayerScore(int score) {
    this -> computerScore += score;
}

int Computer::getScore() {
    return this -> computerScore;
}
