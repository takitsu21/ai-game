//
// Created by antoi on 08/12/2021.
//

#include <thread>
#include <array>

#include "IA.h"

void printTab(array<int*, TAB_VALUES_SIZE> tab) {
    for (int i = 0; i < TAB_VALUES_SIZE; i++) {
        printf("[%d] ", *tab[i]);
    }
    printf("\n------------------------------------\n");
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