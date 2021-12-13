//
// Created by Dylann on 13/12/2021.
//

#include "QuiesceIA.h"

int QuiesceIA::minmax_alphaBeta(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc,
                                bool isJ1, int alpha, int beta) {


    if (currentBoard.isEnd(isJ1)) {
        int score = currentBoard.evaluate(isJ1, AIPlaying, depth, depthMax);
        return score;
    }
    if (depth == depthMax) {
        return quiesce(currentBoard, alpha, beta, AIPlaying, isJ1, depthMax, depthMax + 1);
    }

    int bestMove;
    if (AIPlaying) {
        bestMove = -100;
        for (int i = 0; i < SIZE; i++) {
            for (int colorJ = 0; colorJ < 2; colorJ++) {

                bool isRed = colorJ == 0;

                if (currentBoard.checkValidMove(i, isRed)) {
                    Board nextBoard = currentBoard.copy();
                    nextBoard.play(i, isRed);
                    nextBoard.nextPlayer();
                    *acc = *acc + 1;

                    bestMove = max(bestMove,
                                   minmax_alphaBeta(nextBoard, false, depth + 1, depthMax, acc, isJ1, alpha, beta));

                    alpha = max(alpha, bestMove);
                    if (bestMove >= beta) {
                        break;
                    }
                }
            }
        }
    } else {
        bestMove = 100;
        for (int i = 0; i < SIZE; i++) {
            for (int colorJ = 0; colorJ < 2; colorJ++) {


                bool isRed = colorJ == 0;

                if (currentBoard.checkValidMove(i, isRed)) {
                    Board nextBoard = currentBoard.copy();
                    nextBoard.play(i, isRed);
                    nextBoard.nextPlayer();


                    bestMove = min(bestMove,
                                   minmax_alphaBeta(nextBoard, true, depth + 1, depthMax, acc, isJ1, alpha, beta));

                    beta = min(beta, bestMove);
                    if (bestMove <= alpha) {
                        break;
                    }
                }
            }
        }
    }
    return bestMove;
}
