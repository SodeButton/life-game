//
// Created by button501 on 2022/07/10.
//
// WASDでカーソル（⭕️）を移動。スペースキーでセルを生成。もう一度押すと削除。
// 初期値を入力して、Enterキーでシュミレーション開始。
// 終了は、control+Cでできる。
//

#include <unistd.h>

#include <iostream>

#include "Life.hpp"

int main() {
    GlidWorld world(50, 50);

    while (true) {
        if (world.init()) {
            break;
        }
    }

    while (true) {
        if (world.update()) {
            world.show();
        } else {
            cout << "終了." << endl;
            break;
        }

        usleep(200000);
    }

    return 0;
}
