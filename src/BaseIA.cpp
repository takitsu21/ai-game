//
// Created by antoi on 12/12/2021.
//

#include "BaseIA.h"


int BaseIA::evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) {
    int x;
    int nbJ2Seeds = board.getNbJ2Seeds();
    int nbJ1Seeds = board.getNbJ1Seeds();
    int J2Pieces = board.getNbJ2Pieces();
    int J1Pieces = board.getNbJ1Pieces();
    int nbSeeds = board.getNbSeeds();

    if (isJ1) {
        if (!AIPlaying && nbJ2Seeds <= 0) { // Si on est joueur 1 et qu'on évalue un coup de l'IA
            x = 64;
        } else if (AIPlaying && nbJ1Seeds <= 0) { // on évalue le coup de l'adversaire (J2)
            x = -64;
        } else if (J2Pieces > 32) {
            x = -64;
        } else if (J1Pieces > 32) {
            x = 64;
        } else if (nbSeeds < 8 && J1Pieces < J2Pieces) {
            x = -64;
        } else if (nbSeeds < 8 && J1Pieces > J2Pieces) {
            x = 64;
        } else {
            x = J1Pieces - J2Pieces;
        }
        x += (nbJ1Seeds - nbJ2Seeds) / 10;
    } else {
        if (!AIPlaying && nbJ1Seeds <= 0) { // Si on est joueur 2 et qu'on évalue notre propre coup
            x = 64;
        } else if (AIPlaying && nbJ2Seeds <= 0) { // on évalue le coup de l'adversaire (J2)
            x = -64;
        } else if (J1Pieces > 32) {
            x = -64;
        } else if (J2Pieces > 32) {
            x = 64;
        } else if (nbSeeds < 8 && J2Pieces < J1Pieces) {
            x = -64;
        } else if (nbSeeds < 8 && J2Pieces > J1Pieces) {
            x = 64;
        } else {
            x = J2Pieces - J1Pieces;
        }
        x += (nbJ2Seeds - nbJ1Seeds) / 10;
    }
    x += depthMax - depth;
    return x;
}

int BaseIA::evaluateDepth(Board board, bool isJ1, int depthMax) {
    int nbMoves = 0;
    int depth;
    for (int i = 0; i < SIZE; i++) {

        for (int colorJ = 0; colorJ < 2; colorJ++) {
            bool color_bool = colorJ == 0;
            if (board.checkValidMove(i, color_bool)) {
                nbMoves++;
            }
        }
    }
    if (nbMoves <= 2 && board.getNbSeeds() < 16) {
        depth = depthMax + 4;
    } else if (nbMoves <= 5 && board.getNbSeeds() < 20) {
        depth = depthMax + 3;
    } else if (nbMoves <= 7 && board.getNbSeeds() < 25) {
        depth = depthMax + 2;
    } else if (nbMoves <= 7 && board.getNbSeeds() < 35) {
        depth = depthMax + 1;
    } else if (nbMoves <= 10 && board.getNbSeeds() < 55) {
        depth = depthMax;
    } else { // > 14
        depth = depthMax - 1;
    }
    return depth;
}

int BaseIA::minmax_alphaBeta(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc, bool isJ1,
                             int alpha, int beta) {

    *acc = *acc + 1;

    if (currentBoard.isEnd(isJ1) || depth == depthMax) {
        int score = currentBoard.evaluate(isJ1, AIPlaying, depth, depthMax);
        return score;
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

void
BaseIA::minmax_alphaBetaThread(Board currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc, bool isJ1,
                               int *res) {
    long long acc2 = 0;
    int score = minmax_alphaBeta(currentBoard, AIPlaying, depth, depthMax, &acc2, isJ1, -100, 100);
    *acc = *acc + acc2;
    *res = score;
}

int BaseIA::start(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc, bool isJ1) {
    *acc = *acc + 1;

    array<thread, TAB_VALUES_SIZE> threads;
    array<int *, TAB_VALUES_SIZE> tabValues{};
    for (int i = 0; i < TAB_VALUES_SIZE; i++) {
        tabValues[i] = (int *) malloc(sizeof(int));
        *tabValues[i] = -100;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int colorJ = 0; colorJ < 2; colorJ++) {

            bool isRed = colorJ == 0;

            if (currentBoard.checkValidMove(i, isRed)) {
                Board nextBoard = currentBoard.copy();
                nextBoard.play(i, isRed);
                nextBoard.nextPlayer();

                if (isRed) {
                    threads[i] = thread([=] {
                        minmax_alphaBetaThread(nextBoard, !AIPlaying, depth + 1, depthMax, acc, isJ1, tabValues[i]);
                    });
                } else {
                    threads[i + SIZE] = thread([=] {
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