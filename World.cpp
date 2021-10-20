#include <thread>
#include "World.h"
#include "Grid.h"
#include <ncurses.h>

World::World(Grid *grid) {
    this->grid = grid;
}

void World::start() {

    init();

    do {
        if (!this->isPaused) {
            this->update();
        }

        this->render();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } while (this->isRunning);
}

void World::init() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    grid->init(COLS - 1, LINES - 1);
    initViewport();
    grid->randomize();

    this->inputThread = std::thread(&World::waitForInput, this);
}

void World::update() {
    grid->updateCellStates();
}

void World::render() {

    this->clearScreen();
    this->renderMenu();
    this->renderGrid();
    refresh();
}

void World::waitForInput() {
    do {
        int input = getch();
        handleInput(input);

    } while(this->isRunning);
}

void World::handleInput(const int &input) {
    if (input == 'q') {
        isRunning = false;
    }

    if (input == ' ') {
        isPaused = !isPaused;
    }

    if (input == 'r') {
        grid->randomize();
    }

    if (input == 'c') {
        grid->killAll();
    }

    if (input == '+') {
        viewport.x = 0;
        viewport.y = 0;
        viewport.width += grid->getWidth() * 0.1;
        viewport.height += grid->getHeight() * 0.1;

        // FIXME use std::min() instead
        if (viewport.width > grid->getWidth()) {
            viewport.width = grid->getWidth();
        }
        if (viewport.height > grid->getHeight()) {
            viewport.height = grid->getHeight();
        }
    }

    if (input == '-') {
        viewport.x = 0;
        viewport.y = 0;
        viewport.width -= grid->getWidth() * 0.1;
        viewport.height -= grid->getHeight() * 0.1;

        // FIXME use std::min() instead
        if (viewport.width < 50) {
            viewport.width = 50;
        }
        if (viewport.height < 40) {
            viewport.height = 40;
        }
    }

    if (input == KEY_LEFT) {
        viewport.x -= 10;
        if (viewport.x < 0) {
            viewport.x = 0;
        }
    }

    if (input == KEY_RIGHT) {
        viewport.x += 10;
        int maxX = grid->getWidth() - viewport.width;
        if (viewport.x > maxX) {
            viewport.x = maxX;
        }
    }

    if (input == KEY_DOWN) {
        viewport.y += 10;
        int maxY = grid->getHeight() - viewport.height;
        if (viewport.y > maxY) {
            viewport.y = maxY;
        }
    }

    if (input == KEY_UP) {
        viewport.y -= 10;
        if (viewport.y < 0) {
            viewport.y = 0;
        }
    }
    
}

void World::renderMenu() {
    mvaddstr(LINES-1,0, "Q: quit; C: kill all cells; R: randomize cells; space bar: play/pause; +: zoom in; -: zoom out");
}

void World::renderGrid() {
    for (int x = this->viewport.x; x < this->viewport.x + this->viewport.width; x++) {
        for (int y = this->viewport.y; y < this->viewport.y + this->viewport.height; y++) {
            bool isAlive = this->grid->cells[x][y];
            if (isAlive) {
                mvaddch(y - this->viewport.y, x - this->viewport.x, '*');
            }
        }
    }
}

void World::initViewport() {
    viewport.width = 80;
    viewport.height = 40;
    viewport.x = 0;
    viewport.y = 0;
}

World::~World() {
    inputThread.join();
    endwin();
}

void World::clearScreen() {
    clear();
}
