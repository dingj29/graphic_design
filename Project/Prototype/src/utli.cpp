//
// Created by WILL on 2021/11/15.
//

#include "utli.h"
#include <cstdlib>
#include <ctime>

const float red[3] {1.0f, 0.0f, 0.0f};
const float green[3] {0.0f, 1.0f, 0.0f};
const float blue[3] {0.0f, 0.0f, 1.0f};
const float red_player[3] {1.0f, 0.5f, 0.5f};
const float green_player[3] {0.5f, 1.0f, 0.5f};
const float blue_player[3] {0.5f, 0.5f, 1.0f};

int utli::random_int(int low, int up) {
    return low + rand() % (up - low + 1);
}

void utli::init() {
    srand(time(nullptr));
}

float utli::random_float(float low, float up) {
    return static_cast <float> (low + (rand()) / static_cast <float> (RAND_MAX/(up - low)));
}

float *utli::get_color(int color) {
    switch (color) {
        case 1:
            return const_cast<float *>(red);
        case 2:
            return const_cast<float *>(green);
        case 3:
            return const_cast<float *>(blue);
        case 4:
            return const_cast<float *>(red_player);
        case 5:
            return const_cast<float *>(green_player);
        case 6:
            return const_cast<float *>(blue_player);
        default:
            break;
    }

    return nullptr;
}
