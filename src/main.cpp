#include "raylib.h"
#include "src/maze/maze.h"
#include "src/renderer/render.h"
#include "src/algorithm/bfs.h"

int main() {
    const int SCREEN_W = 900;
    const int SCREEN_H = 700;
    const int CELL_SIZE = 20;
    const int ROWS = 25;
    const int COLS = 35;
    const int STEPS_PER_FRAME = 3;

    InitWindow(SCREEN_W, SCREEN_H, "Maze Pathfinder - BFS");
    SetTargetFPS(60);

    Maze maze(ROWS, COLS);
    Renderer  renderer(CELL_SIZE);
    BFSSolver bfs;

    maze.generate();

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_R)) {
            maze.generate();
            bfs = BFSSolver();
        }

        if (IsKeyPressed(KEY_ONE))
            bfs.init(maze);

        if (bfs.getState() == SolverState::SEARCHING)
            for (int i = 0; i < STEPS_PER_FRAME; ++i) {
                bfs.step(maze);
                if (bfs.getState() != SolverState::SEARCHING) break;
            }

        BeginDrawing();
            ClearBackground(BLACK);
            renderer.drawVisited(maze, bfs.getVisited());
            if (bfs.getState() == SolverState::DONE)
                renderer.drawPath(maze, bfs.getPath());
            renderer.drawMaze(maze);
            renderer.drawStartEnd(maze);
            renderer.drawUI(bfs.getState());
        EndDrawing();
    }

    CloseWindow();
    return 0;
}