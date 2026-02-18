#pragma once
#include "raylib.h"
#include "src/maze/maze.h"

class Renderer {
public:
    Renderer(int cellSize);

    void drawMaze(const Maze& maze);
    void drawStartEnd(const Maze& maze);

private:
    int cellSize_;
    int offsetX_;
    int offsetY_;

    void computeOffset(const Maze& maze);
};