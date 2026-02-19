#include "render.h"

Renderer::Renderer(int cellSize)
    : cellSize_(cellSize), offsetX_(0), offsetY_(0)
{}


void Renderer::computeOffset(const Maze& maze) {
    int mazePixelW = maze.getCols() * cellSize_;
    int mazePixelH = maze.getRows() * cellSize_;
    offsetX_ = (GetScreenWidth()  - mazePixelW) / 2;
    offsetY_ = (GetScreenHeight() - mazePixelH) / 2;
}

//draw maze walls
void Renderer::drawMaze(const Maze& maze) {
    computeOffset(maze);

    int cs = cellSize_;

    for (int r = 0; r < maze.getRows(); ++r) {
        for (int c = 0; c < maze.getCols(); ++c) {

            const Cell& cell = maze.getCell(r, c);

            int x = offsetX_ + c * cs;   // pixel x of cell's top-left corner
            int y = offsetY_ + r * cs;   // pixel y of cell's top-left corner

            Color wallColor = WHITE;

            // Top wall
            if (cell.wallTop)
                DrawLine(x,y,x + cs,y,wallColor);

            // Bottom wall
            if (cell.wallBottom)
                DrawLine(x,y + cs, x + cs, y + cs, wallColor);

            // Left wall
            if (cell.wallLeft)
                DrawLine(x,y,x, y + cs, wallColor);

            // Right wall
            if (cell.wallRight)
                DrawLine(x + cs, y, x + cs, y + cs, wallColor);
        }
    }
}

void Renderer::drawVisited(const Maze& maze, const std::vector<Position>& visited) {
    int cs = cellSize_;
    Color c = { 50, 130, 200, 160 };
    for (const auto& pos : visited)
        DrawRectangle(px(pos.second) + 1, py(pos.first) + 1, cs - 2, cs - 2, c);
}

void Renderer::drawPath(const Maze& maze, const std::vector<Position>& path) {
    int cs = cellSize_;
    Color c = { 255, 220, 0, 220 };
    for (const auto& pos : path)
        DrawRectangle(px(pos.second) + 2, py(pos.first) + 2, cs - 4, cs - 4, c);
}

void Renderer::drawStartEnd(const Maze& maze) {
    int cs = cellSize_;
    DrawRectangle(px(maze.startCol) + 2, py(maze.startRow) + 2, cs - 4, cs - 4, GREEN);
    DrawRectangle(px(maze.endCol)   + 2, py(maze.endRow)   + 2, cs - 4, cs - 4, RED);
}

void Renderer::drawUI(SolverState state) {
    DrawText("R - New maze",        10, 10, 16, GRAY);
    DrawText("1 - BFS pathfinding", 10, 30, 16, GRAY);

    const char* msg = "";
    Color col = GRAY;
    if      (state == SolverState::IDLE)      { msg = "Press 1 to start BFS"; col = LIGHTGRAY; }
    else if (state == SolverState::SEARCHING) { msg = "BFS searching...";      col = SKYBLUE;   }
    else if (state == SolverState::DONE)      { msg = "Path found!";           col = YELLOW;    }
    else if (state == SolverState::NO_PATH)   { msg = "No path found.";        col = RED;       }

    DrawText(msg, 10, GetScreenHeight() - 28, 18, col);
}