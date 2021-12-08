//
// Created by antoi on 08/12/2021.
//

#include "IA.h"


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

int negamax(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc, bool isJ1, bool firstCall) {
    int tabValues[TAB_VALUES_SIZE];
    *acc = *acc + 1;

    if (currentBoard.isEnd()) {
        if (AIPlaying) {
            return 64;
        }
        else {
            return -64;
        }
    }

    if (depth == depthMax) {
        int score = currentBoard.evaluate(isJ1);
        return score;
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

                bestMove = negamax(nextBoard, !AIPlaying, depth + 1, depthMax, acc, isJ1, false);

                if (isRed) { // if red
                    tabValues[i] = bestMove;
                } else { // if blue
                    tabValues[i + SIZE] = bestMove;
                }
            }
            else {
                if (AIPlaying) {
                    if (isRed) { // if red
                        tabValues[i] = -100;
                    } else { // if blue
                        tabValues[i + SIZE] = -100;
                    }
                } else {
                    if (isRed) { // if red tabvalues 16
                        tabValues[i] = 100;
                    } else { // if blue tabvalues >= 16
                        tabValues[i + SIZE] = 100;
                    }
                }
            }
        }
    }

    int res;
    if (firstCall) {
        if (AIPlaying) {
            res = maxFromArray(tabValues);
        } else {
            res = minFromArray(tabValues);
        }
    }
    else {
        int idx;
        if (AIPlaying) {
            idx = maxFromArray(tabValues);
        } else {
            idx = minFromArray(tabValues);
        }
        res = tabValues[idx];
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
    if (nbMoves <= 8) {
        depth = depthMax+1;
    }
    else if (nbMoves <= 10) {
        depth = depthMax;
    }
    else { // > 14
        depth = depthMax-1;
    }
    return depth;
}
