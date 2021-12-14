//
// Created by antoi on 08/12/2021.
//

#include <thread>
#include <array>

#include "IA.h"
#include <utility>
#include <algorithm>
#include <iterator>

bool myCompare(const std::pair<int, pair<int, bool>> &p1, const std::pair<int, pair<int, bool>> &p2) {
    return p1.first > p2.first;
}

int maxFromArrayPtr(array<int*, TAB_VALUES_SIZE> tabValues) {
    int maxBlue = -100;
    int idxBlue = 0;
    int maxRed = -100;
    int idxRed = 0;

    for (int i = 0; i < SIZE; i++) { // MAX RED
        if (*tabValues[i] > maxRed) {
            maxRed = *tabValues[i];
            idxRed = i;
        }
    }

    for (int i = SIZE; i < TAB_VALUES_SIZE; i++) { // MAX BLUE
        if (*tabValues[i] > maxBlue) {
            maxBlue = *tabValues[i];
            idxBlue = i;
        }
    }

    if (maxBlue > maxRed) {
        return idxBlue;
    } else {
        return idxRed;
    }
}