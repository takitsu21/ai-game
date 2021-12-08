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
    int maxBlue = 100;
    int idxBlue = 0;
    int maxRed = 100;
    int idxRed = 0;

    for (int i = 0; i < SIZE; i++) { // MIN RED
        if (tabValues[i] < maxRed) {
            maxRed = tabValues[i];
            idxRed = i;
        }
    }

    for (int i = SIZE; i < TAB_VALUES_SIZE; i++) { // MIN BLUE
        if (tabValues[i] < maxBlue) {
            maxBlue = tabValues[i];
            idxBlue = i;
        }
    }

    if (maxBlue > maxRed) {
        return idxRed;
    } else {
        return idxBlue;
    }
}

int negamax(Board &currentBoard, bool AIPlaying, int depth, int depthMax, int alpha, int beta, long long *acc, bool isJ1, int *winNbMove) {
    int tabValues[TAB_VALUES_SIZE];
    *acc = *acc + 1;

    if (depth >= *winNbMove) {
        return 0;
    }
    if (currentBoard.isEnd() || depth == depthMax) {
        int score = currentBoard.evaluate(isJ1);

        if (AIPlaying) {
            if (score == 64) { // Win
                *winNbMove = depth;
                cout << "WIIN " << *winNbMove << endl;
                return 100;
            }
            return 1 * (score);
        } else {
            return -1 * (score);
        }
    }
    int bestMove = -100;
    for (int i = 0; i < SIZE; i++) {

        for (int colorJ = 0; colorJ < 2; colorJ++) {
            Board nextBoard = currentBoard.copy();
            bool color_bool = colorJ == 0;

            if (nextBoard.checkValidMove(i, color_bool)) {
                if (nextBoard.play(i, color_bool)) {
                    nextBoard.nextPlayer();
                }

                bestMove = max(bestMove, -negamax(nextBoard, !AIPlaying, depth + 1, depthMax,
                                                  -beta, -alpha, acc, isJ1, winNbMove));
                alpha = max(alpha, bestMove);

                if (alpha >= beta) { // peut etre renvoyé le best move
                    if (color_bool) {
                        return i;
                    } else {
                        return i + SIZE;
                    }
                }
                if (color_bool) { // if red
                    tabValues[i] = bestMove;
                } else { // if blue
                    tabValues[i + SIZE] = bestMove;
                }
            } else {
                if (AIPlaying) {
                    if (color_bool) { // if red
                        tabValues[i] = -100;
                    } else { // if blue
                        tabValues[i + SIZE] = -100;
                    }
                } else {
                    if (color_bool) { // if red tabvalues 16
                        tabValues[i] = 100;
                    } else { // if blue tabvalues >= 16
                        tabValues[i + SIZE] = 100;
                    }
                }
            }
        }
    }

    int res;
    if (AIPlaying) {
        res = maxFromArray(tabValues);
    } else {
        res = minFromArray(tabValues);
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
