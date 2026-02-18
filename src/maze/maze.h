#pragma once
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>

struct Cell {
    int  row, col;

    //true wall = blocked // false wall = open
    bool wallTop    = true;
    bool wallBottom = true;
    bool wallLeft   = true;
    bool wallRight  = true;

    bool visited    = false; //for maze generation and pathfinding
};

class Maze {
public:
    Maze(int rows, int cols);

    // new maze each time
    void generate();

    // Reset only the visited flags 
    void resetVisited();

    int  getRows()  const { return rows_; }
    int  getCols()  const { return cols_; }
    Cell& getCell(int row, int col) { return grid_[row][col]; }
    const Cell& getCell(int row, int col) const { return grid_[row][col]; }

private:
    int rows_, cols_;
    std::vector<std::vector<Cell>> grid_;

public:
    int startRow = 0,  startCol = 0;
    int endRow = 0, endCol = 0;

    void initGrid();
    void carve(int row, int col);       // recursive-backtracker core
    void removeWall(Cell& current, Cell& next, int dr, int dc);
    bool inBounds(int row, int col) const;
};