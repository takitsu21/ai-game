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

int maxFromArray(const int *tabValues) {
    int maxBlue = -100;
    int idxBlue = 0;
    int maxRed = -100;
    int idxRed = 0;

    for (int i = 0; i < SIZE; i++) { // MAX RED
        if (tabValues[i] > maxRed) {
            maxRed = tabValues[i];
            idxRed = i;
        }
    }

    for (int i = SIZE; i < TAB_VALUES_SIZE; i++) { // MAX BLUE
        if (tabValues[i] > maxBlue) {
            maxBlue = tabValues[i];
            idxBlue = i;
        }
    }

    if (maxBlue > maxRed) {
        return idxBlue;
    } else {
        return idxRed;
    }
}

int minFromArray(const int *tabValues) {
    int minBlue = 100;
    int idxBlue = 0;
    int minRed = 100;
    int idxRed = 0;

    for (int i = 0; i < SIZE; i++) { // MIN RED
        if (tabValues[i] < minRed) {
            minRed = tabValues[i];
            idxRed = i;
        }
    }

    for (int i = SIZE; i < TAB_VALUES_SIZE; i++) { // MIN BLUE
        if (tabValues[i] < minBlue) {
            minBlue = tabValues[i];
            idxBlue = i;
        }
    }

    if (minRed < minBlue) {
        return idxRed;
    } else {
        return idxBlue;
    }
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

int minmax_alphaBeta(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc, bool isJ1) {

    *acc = *acc + 1;

    if (currentBoard.isEnd(isJ1) || depth == depthMax) {
        int score = currentBoard.evaluate(isJ1, AIPlaying, depth, depthMax);
        return score;
    }

    int tabValues[TAB_VALUES_SIZE] = {
            -100, -100, -100, -100,
            -100, -100, -100, -100,
            -100, -100, -100, -100,
            -100, -100, -100, -100,
            -100, -100, -100, -100,
            -100, -100, -100, -100,
            -100, -100, -100, -100,
            -100, -100, -100, -100
    };
    if (!AIPlaying) {
        for (int & tabValue : tabValues) {
            tabValue = 100;
        }
    }

    int bestMove;

    for (int i = 0; i < SIZE; i++) {
        for (int colorJ = 0; colorJ < 2; colorJ++) {

            Board nextBoard = currentBoard.copy();
            bool isRed = colorJ == 0;

            if (nextBoard.checkValidMove(i, isRed)) {
                if (nextBoard.play(i, isRed)) {
                    nextBoard.nextPlayer();
                }


                bestMove = minmax_alphaBeta(nextBoard, !AIPlaying, depth + 1, depthMax, acc, isJ1);

                if (isRed) { // if red
                    tabValues[i] = bestMove;
                } else { // if blue
                    tabValues[i + SIZE] = bestMove;
                }
            }
        }
    }

    int res;

    int idx;
    if (AIPlaying) {
        idx = maxFromArray(tabValues);
    } else {
        idx = minFromArray(tabValues);
    }
    res = tabValues[idx];

    return res;
}

void minmax_alphaBetaThread(Board currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc, bool isJ1, int *res) {
    int score = minmax_alphaBeta(currentBoard, AIPlaying, depth, depthMax, acc, isJ1);
    *res = score;
}

int minmax_alphaBetaStart(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc, bool isJ1) {
    *acc = *acc + 1;

    array<thread, TAB_VALUES_SIZE> threads;
    array<int*, TAB_VALUES_SIZE> tabValues{};
    for (int i = 0; i < TAB_VALUES_SIZE; i++) {
        tabValues[i] = (int *) malloc(sizeof(int));
        *tabValues[i] = -100;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int colorJ = 0; colorJ < 2; colorJ++) {

            Board nextBoard = currentBoard.copy();
            bool isRed = colorJ == 0;

            if (nextBoard.checkValidMove(i, isRed)) {
                if (nextBoard.play(i, isRed)) {
                    nextBoard.nextPlayer();
                }

                if (isRed) {
                    threads[i] = thread( [=] {
                        minmax_alphaBetaThread(nextBoard, !AIPlaying, depth + 1, depthMax, acc, isJ1, tabValues[i]);
                    });
                }
                else {
                    threads[i+SIZE] = thread( [=] {
                        minmax_alphaBetaThread(nextBoard, !AIPlaying, depth + 1, depthMax, acc, isJ1,
                                               tabValues[i + SIZE]);
                    });
                }
            }
        }
    }

    for (int i = 0; i < TAB_VALUES_SIZE; i++) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }

    int res;
    res = maxFromArrayPtr(tabValues);

    for (int i = 0; i < TAB_VALUES_SIZE; i++) {
        delete tabValues[i];
    }
    return res;
}

int evaluateDepth(Board board, bool isJ1, int depthMax) {
    int nbMoves = 0;
    int depth;
    for (int i = 0; i < SIZE; i++) {

        for (int colorJ = 0; colorJ < 2; colorJ++) {
            Board nextBoard = board.copy();
            bool color_bool = colorJ == 0;
            if (nextBoard.checkValidMove(i, color_bool)) {
                nbMoves++;
            }
        }
    }
    if (nbMoves <= 2) {
        depth = depthMax + 3;
    } else if (nbMoves <= 7) {
        depth = depthMax + 2;
    } else if (nbMoves <= 8) {
        depth = depthMax + 1;
    } else if (nbMoves <= 10) {
        depth = depthMax;
    } else { // > 14
        depth = depthMax - 1;
    }
    return depth;
}
