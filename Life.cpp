//
// Created by hw21a105 on 2022/07/10.
//

#include "Life.hpp"

#include <cstdlib>
#include <iostream>

#include "conio.hpp"
using namespace std;

GlidWorld::GlidWorld(int _width, int _height) {
    width = _width;
    height = _height;

    cell_a.assign(width, vector<bool>(height, false));
    cell_b.assign(width, vector<bool>(height, false));
}

void GlidWorld::show() {
    system("clear");
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (cell_b[x][y]) {
                cout << "⬜️";
            } else {
                cout << "・";
            }
        }
        cout << endl;
    }
}

int GlidWorld::getAdjacentLivesCount(int _x, int _y) {
    int count = 0;
    vector<int> p{-1, -1, -1, 0, 0, 1, 1, 1}, q{-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        int x2 = (width + _x + p[i]) % width;
        int y2 = (height + _y + q[i]) % height;
        if (cell_a[x2][y2]) count++;
    }

    return count;
}

void GlidWorld::update() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int n = getAdjacentLivesCount(x, y);
            bool next = cell_a[x][y];

            if (cell_a[x][y]) {
                if (n <= 1 || n >= 4) {
                    next = false;
                }
            } else {
                if (n == 3) {
                    next = true;
                }
            }

            cell_b[x][y] = next;
        }
    }
    cell_a = cell_b;
}

bool GlidWorld::init() {
    system("clear");
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (x == cursorX && y == cursorY) {
                cout << "⭕️";
            } else if (cell_a[x][y]) {
                cout << "⬜️";
            } else {
                cout << "・";
            }
        }
        cout << endl;
    }

    switch (getch()) {
        case 'w':
            cursorX = (width + cursorX - 1) % width;
            break;
        case 'a':
            cursorY = (height + cursorY - 1) % height;
            break;
        case 's':
            cursorX = (cursorX + 1) % width;
            break;
        case 'd':
            cursorY = (cursorY + 1) % height;
            break;
        case ' ':
            cell_a[cursorX][cursorY] = !cell_a[cursorX][cursorY];
            break;
        case '\n':
            return true;
    }

    return false;
}