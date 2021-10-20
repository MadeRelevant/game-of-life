#include <vector>
#include "World.h"

using namespace std;

int main() {

    World game(new Grid());
    game.start();

    return 0;
}
