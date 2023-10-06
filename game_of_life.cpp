#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to create row boundary
void row_line(int col)
{
    cout << endl;
    for (int i = 0; i < col; i++) {
        cout << " ---";
    }
    cout << endl;
}

enum CellState {
    DEAD = 0,
    ALIVE = 1
};

class GameOfLife {
public:
    GameOfLife(int rows, int cols);
    void initialize();
    void print(const string& title) const;
    void evolve();
    bool isStable() const;
    int getGeneration() const;
    int getMaxGeneration() const;

private:
    int rows;
    int cols;
    int generation;
    vector<vector<CellState>> currentGrid;
    vector<vector<CellState>> nextGrid;
    void randomizeGrid();
    int countLiveNeighborCells(int row, int col) const;
};

GameOfLife::GameOfLife(int rows, int cols) : 
    rows(rows), 
    cols(cols),
    generation(0), // Initialize generation counter
    currentGrid(rows, vector<CellState>(cols)),
    nextGrid(rows, vector<CellState>(cols))
{
    srand(time(nullptr)); // Seed random number generator
}

void GameOfLife::randomizeGrid()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            currentGrid[i][j] = static_cast<CellState>(rand() % 2);
        }
    }
}

void GameOfLife::initialize()
{
    randomizeGrid();
}

int GameOfLife::countLiveNeighborCells(int row, int col) const
{
    int count = 0;

    // Define relative positions of neighbors (8 possible neighbors)
    int neighbors[][2] = {
        {-1, -1}, {-1, 0},  {-1, 1},
        {0, -1},            {0, 1},
        {1, -1},  {1, 0},   {1, 1}
    };

    // Loop through all eight possible neighbors
    for (int i = 0; i < 8; i++) {
        // Calculate the coordinates of the current neighbor
        int neighborRow = row + neighbors[i][0];
        int neighborCol = col + neighbors[i][1];

        // Check if the neighbor is within bounds and alive
        if (neighborRow >= 0 && neighborRow < rows && neighborCol >= 0 && neighborCol < cols &&
            currentGrid[neighborRow][neighborCol] == ALIVE) {
            count++;
        }
    }

    return count;
}

int GameOfLife::getGeneration() const {
    return generation;
}

void GameOfLife::evolve()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighborLiveCellCount = countLiveNeighborCells(i, j);
            if (currentGrid[i][j] == ALIVE && (neighborLiveCellCount == 2 || neighborLiveCellCount == 3)) {
                nextGrid[i][j] = ALIVE;
            } else if (currentGrid[i][j] == DEAD && neighborLiveCellCount == 3) {
                nextGrid[i][j] = ALIVE;
            } else {
                nextGrid[i][j] = DEAD;
            }
        }
    }

    swap(currentGrid, nextGrid);
    generation++;
}

bool GameOfLife::isStable() const
{
    // Compare each cell in the current and next grids
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (currentGrid[i][j] != nextGrid[i][j]) {
                return false; 
            }
        }
    }
    return true;
}

void GameOfLife::print(const string& title) const
{
    cout << title << " (Generation " << generation << "):";
    row_line(cols);
    for (int i = 0; i < rows; i++) {
        cout << ":";
        for (int j = 0; j < cols; j++) {
            cout << " " << static_cast<int>(currentGrid[i][j]) << " :";
        }
        row_line(cols);
    }
}

int main()
{
    int row, col, maxGenerations;
    
    cout << "Enter the number of rows: ";
    cin >> row;
    
    cout << "Enter the number of columns: ";
    cin >> col;
    
    cout << "Enter the maximum number of generations: ";
    cin >> maxGenerations;

    GameOfLife game(row, col);
    game.initialize();

    cout << endl;
    game.print("Initial Stage");

    while (!game.isStable() && game.getGeneration() < maxGenerations) {
        game.evolve();
        game.print("Next Generation");
    }

    if (game.isStable()) {
        cout << "The game has reached a stable state." << endl;
    } else {
        cout << "The maximum number of generations (" << maxGenerations << ") has been reached." << endl;
    }

    return 0;
}
