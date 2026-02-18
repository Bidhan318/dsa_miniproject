#include "src/maze/maze.h"
#include <algorithm>

Maze::Maze(int rows, int cols)
    : rows_(rows), cols_(cols),
      endRow(rows - 1), endCol(cols - 1)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    initGrid();
}

void Maze::initGrid() {
    grid_.assign(rows_, std::vector<Cell>(cols_));
    for (int r = 0; r < rows_; ++r)
        for (int c = 0; c < cols_; ++c) {
            grid_[r][c].row  = r;
            grid_[r][c].col  = c;
            grid_[r][c].wallTop    = true;
            grid_[r][c].wallBottom = true;
            grid_[r][c].wallLeft   = true;
            grid_[r][c].wallRight  = true;
            grid_[r][c].visited    = false;
        }
}

void Maze::generate() {
    initGrid();

    // Fix start and end corners
    startRow = 0;
    startCol = 0;
    endRow   = rows_ - 1;
    endCol   = cols_ - 1;

    carve(startRow, startCol);
}

void Maze::resetVisited() {
    for (int r = 0; r < rows_; ++r)
        for (int c = 0; c < cols_; ++c)
            grid_[r][c].visited = false;
}

bool Maze::inBounds(int row, int col) const {
    return row >= 0 && row < rows_ && col >= 0 && col < cols_;
}

void Maze::removeWall(Cell& cur, Cell& nxt, int dr, int dc) {
    if (dr == -1) { cur.wallTop    = false; nxt.wallBottom = false; } // moved up
    if (dr ==  1) { cur.wallBottom = false; nxt.wallTop    = false; } // moved down
    if (dc == -1) { cur.wallLeft   = false; nxt.wallRight  = false; } // moved left
    if (dc ==  1) { cur.wallRight  = false; nxt.wallLeft   = false; } // moved right
}


//recusrive backtracking algorithm
void Maze::carve(int row, int col) {

    grid_[row][col].visited = true;

    // Four cardinal directions: {dRow, dCol}
    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

    // Shuffle directions using Fisher-Yates
    for (int i = 3; i > 0; --i) {
        int j = std::rand() % (i + 1);
        std::swap(dirs[i][0], dirs[j][0]);
        std::swap(dirs[i][1], dirs[j][1]);
    }

    for (auto& d : dirs) {
        int nr = row + d[0];
        int nc = col + d[1];

        if (inBounds(nr, nc) && !grid_[nr][nc].visited) {
            removeWall(grid_[row][col], grid_[nr][nc], d[0], d[1]);
            carve(nr, nc);          // recurse into neighbour
        }
    }
    // Implicit backtrack: function returns, caller tries next direction
}