//
// Created by hw21a105 on 2022/07/10.
//

#ifndef LIFEGAME_LIFE_HPP
#define LIFEGAME_LIFE_HPP

#include <vector>
using namespace std;

class GlidWorld {
    int cursorX = 0;
    int cursorY = 0;
    int width = 24;
    int height = 24;

    vector<vector<bool>> cell_a;
    vector<vector<bool>> cell_b;

   public:
    GlidWorld(int _width, int _height);
    int getAdjacentLivesCount(int _x, int _y);
    void update();
    bool init();
    void show();
};

#endif  // LIFEGAME_LIFE_HPP
