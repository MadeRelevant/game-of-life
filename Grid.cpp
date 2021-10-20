#include "Grid.h"
#include <random>

using namespace std;

void Grid::init(int width, int height) {

    this->width = width;
    this->height = height;

    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            this->cells[x][y] = false;
        }
    }
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}

void Grid::updateCellStates() {

    for (int x = 0; x < this->cells.size(); x++) {
        for (int y = 0; y < this->cells[x].size(); y++) {
            int numLifeNeighbors = this->getNumOfLifeNeighbors(x, y);
            int numDeadNeighbors = 8 - numLifeNeighbors;

            cells[x][y] = shouldBeAlive(x, y, numLifeNeighbors, numDeadNeighbors);
        }
    }
}

bool Grid::shouldBeAlive(int x, int y, int numLifeNeighbors, int numDeadNeighbors) {
    bool isAlive = cells[x][y];

    if (isAlive) {

        // a life cell with less than 2 life neighbors dies
        if (numLifeNeighbors < 2) {
            return false;
        }

        // a life cell with 2 or 3 life neighbors lives on
        if (numLifeNeighbors == 2 || numLifeNeighbors == 3) {
            return true;
        }

        // a life cell with more than 3 life neighbors dies
        if (numLifeNeighbors > 3) {
            return false;
        }
    } else {
        if (numLifeNeighbors == 3) {
            // revive
            return true;
        }
    }

    return isAlive;
}

int Grid::getNumOfLifeNeighbors(int x, int y) {
    /**
     1      2       3
     8      X       4
     7      6       5
     */

    // Draw a virtual rectangle around the X and return how many are alive
    int minX = x - 1;
    int maxX = x + 1;
    int minY = y - 1;
    int maxY = y + 1;

    return this->getNumberOfLifeCellsInRectangle(minX, maxX, minY, maxY);
}

int Grid::getNumberOfLifeCellsInRectangle(int minX, int maxX, int minY, int maxY) {

    int numAlive = 0;

    for (int x = minX; x <= maxX; x++) {

        if (x < 0 || x > this->cells.size() - 1) {
            // prob somewhere around an edge of the grid, skip those cells
            continue;
        }

        for (int y = minY; y <= maxY; y++) {

            // don't get of the grid and skip those at the edges
            if (y > this->cells[x].size() - 1) {
                continue;
            }

            numAlive += this->cells[x][y] ? 1 : 0;
        }
    }

    return numAlive;
}

void Grid::randomize() {
    for (int x = 0; x < cells.size(); x++) {
        for (int y = 0; y < cells.size(); y++) {
            bool b = getRandomBoolean(0.5);
            cells[x][y] = b;
        }
    }
}

template <typename Prob>
bool Grid::getRandomBoolean(Prob p) {
    static auto dev = std::random_device();
    static auto gen = std::mt19937{dev()};
    static auto dist = std::uniform_real_distribution<Prob>(0,1);
    return (dist(gen) < p);
}

void Grid::killAll() {
    for (int x = 0; x < cells.size(); x++) {
        for (int y = 0; y < cells.size(); y++) {
            cells[x][y] = false;
        }
    }
}
