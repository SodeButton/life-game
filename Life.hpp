//
// Created by button501 on 2022/07/10.
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

    bool is_exit = false;

    vector<vector<bool>> cell_a;
    vector<vector<bool>> cell_b;

   public:
    GlidWorld(int _width, int _height);
    int getAdjacentLivesCount(int _x, int _y);
    void changeGeneration();
    bool update();
    bool init();
    void show();
};

#endif  // LIFEGAME_LIFE_HPP
