#ifndef GAMEOFLIFE_GRID_H
#define GAMEOFLIFE_GRID_H

#include <vector>
#include <map>

using namespace std;

class Grid {
    int width = 0;
    int height = 0;

public:
    void init(int width, int height);
    void updateCellStates();
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;

    int getNumOfLifeNeighbors(int x, int y);

    int getNumberOfLifeCellsInRectangle(int minX, int maxX, int minY, int maxY);

    bool shouldBeAlive(int x, int y, int numLifeNeighbors, int numDeadNeighbors);

    void randomize();

    template <typename Prob>
    bool getRandomBoolean(Prob p);

    void killAll();

    std::map<int, std::map<int, bool>> cells;
};


#endif //GAMEOFLIFE_GRID_H
