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

int quiesce(Board board, int alpha, int beta, bool AIPlaying, bool isJ1, int depth, int depthMax) {
    int standPat = board.evaluate(isJ1, AIPlaying, depth, depthMax);

    if (standPat >= beta) {
        return beta;
    }
    if (alpha < standPat) {
        alpha = standPat;
    }
    if (depthMax == depth) {
        return (AIPlaying ? 1 : -1) * standPat;
    }
    int score;
    for (int i = 0; i < SIZE; i++) {
        for (int color = 0; color < 2; color++) {
            bool isRed = color == 0;
            if (board.checkValidMove(i, isRed)) {
                Board nextBoard = board.copy();
                nextBoard.play(i, isRed);
                nextBoard.nextPlayer();


                score = -quiesce(nextBoard, -beta, -alpha, !AIPlaying, isJ1, depth + 1, depthMax);
                if (score >= beta) {
                    return beta;
                }
                if (score > alpha) {
                    alpha = score;
                }

            }

        }
    }
    return alpha;
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