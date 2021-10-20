#ifndef GAMEOFLIFE_WORLD_H
#define GAMEOFLIFE_WORLD_H

#include <cmath>
#include "Grid.h"
#include <thread>

struct Viewport {
    int x;
    int y;
    int width;
    int height;
};

class World {
    void initViewport();
    bool isRunning = true;
    bool isPaused = false;
    std::thread inputThread;

    void update();

    void render();

    void waitForInput();

    void renderMenu();

    void renderGrid();

    void handleInput(const int &input);

    void clearScreen();
    void init();

public:
    Grid* grid;
    Viewport viewport {};
    World(Grid* grid);
    ~World();

    void start();
};


#endif //GAMEOFLIFE_WORLD_H
