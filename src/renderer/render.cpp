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

void Renderer::drawStartEnd(const Maze& maze) {
    int cs = cellSize_;

    // Start — green
    int sx = offsetX_ + maze.startCol * cs + 2;
    int sy = offsetY_ + maze.startRow * cs + 2;
    DrawRectangle(sx, sy, cs - 4, cs - 4, GREEN);

    // End — red
    int ex = offsetX_ + maze.endCol * cs + 2;
    int ey = offsetY_ + maze.endRow * cs + 2;
    DrawRectangle(ex, ey, cs - 4, cs - 4, RED);
}