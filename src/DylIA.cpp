//
// Created by Dylann on 13/12/2021.
//

#include "DylIA.h"
#include "IA.h"

int DylIA::evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) {
    int nbJ2Seeds = board.getNbJ2Seeds();
    int nbJ1Seeds = board.getNbJ1Seeds();
    int J2Pieces = board.getNbJ2Pieces();
    int J1Pieces = board.getNbJ1Pieces();
    int nbSeeds = board.getNbSeeds();

    if (isJ1) {
        if (AIPlaying) {
            if (nbJ1Seeds <= 0) { // on évalue le coup de l'adversaire (J2)
                return -64;
            } else if (J2Pieces > 32) {
                return -64;
            } else if (nbSeeds < 8 && J1Pieces < J2Pieces) {
                return -64;
            }
        } else {
            if (nbJ2Seeds <= 0) { // Si on est joueur 2 et qu'on évalue notre propre coup
                return 64 + depthMax - depth;
            } else if (nbSeeds < 8 && J1Pieces > J2Pieces) {
                return 64 + depthMax - depth;
            } else if (J1Pieces > 32) {
                return 64 + depthMax - depth;
            }
        }
        int x;
        x = J1Pieces - J2Pieces;
        x += (nbJ1Seeds - nbJ2Seeds) / 10;
        return x;
    } else {
        if (AIPlaying) {
            if (nbJ2Seeds <= 0) { // on évalue le coup de l'adversaire (J2)
                return -64;
            } else if (J1Pieces > 32) {
                return -64;
            } else if (nbSeeds < 8 && J2Pieces < J1Pieces) {
                return -64;
            }
        } else {
            if (nbJ1Seeds <= 0) { // Si on est joueur 2 et qu'on évalue notre propre coup
                return 64 + depthMax - depth;
            } else if (nbSeeds < 8 && J2Pieces > J1Pieces) {
                return 64 + depthMax - depth;
            } else if (J2Pieces > 32) {
                return 64 + depthMax - depth;
            }
        }
        int x;
        x = J2Pieces - J1Pieces;
        x += (nbJ2Seeds - nbJ1Seeds) / 10;
        return x;
    }
}

DylIA::~DylIA() {

}

DylIA::DylIA() {

}

int DylIA::minmax_alphaBeta(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long int *acc, bool isJ1,
                            int alpha, int beta) {

    if (currentBoard.isEnd(isJ1) || depth == depthMax) {
        int score = evaluate(currentBoard, isJ1, AIPlaying, depth, depthMax);
        return score;
    }

    int bestMove;
    array<pair<int, pair<int, bool>>, TAB_VALUES_SIZE> moves{};
    for (int i = 0; i < SIZE; i++) {
        for (int colorJ = 0; colorJ < 2; colorJ++) {
            bool isRed = colorJ == 0;
            if (currentBoard.checkValidMove(i, isRed)) {
                int score = evaluate(currentBoard, isJ1, AIPlaying, depth, depthMax);
                if (isRed) {
                    moves[i] = make_pair(score,
                                         make_pair(i, isRed));
                } else {
                    moves[i + SIZE] = make_pair(score,
                                                make_pair(i, isRed));
                }


            }
        }
    }

    std::sort(std::begin(moves), std::end(moves), myCompare);


    if (AIPlaying) {
        bestMove = -100;
        for (int i = 0; i < TAB_VALUES_SIZE; i++) {
            int x = moves[i].second.first;
            bool isRed = moves[i].second.second;
            if (currentBoard.checkValidMove(x, isRed)) {
                Board nextBoard = currentBoard.copy();
                nextBoard.play(x, isRed);
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
    } else {
        bestMove = 100;
        for (int i = 0; i < TAB_VALUES_SIZE; i++) {
            int x = moves[i].second.first;
            bool isRed = moves[i].second.second;
            if (currentBoard.checkValidMove(x, isRed)) {
                Board nextBoard = currentBoard.copy();
                nextBoard.play(x, isRed);
                nextBoard.nextPlayer();
                *acc = *acc + 1;

                bestMove = min(bestMove,
                               minmax_alphaBeta(nextBoard, true, depth + 1, depthMax, acc, isJ1, alpha, beta));

                beta = min(beta, bestMove);
                if (bestMove <= alpha) {
                    break;
                }
            }

        }


    }
//    }

//
//    else {
//        if (AIPlaying) {
//            bestMove = -100;
//            for (int i = 0; i < SIZE; i++) {
//                for (int colorJ = 0; colorJ < 2; colorJ++) {
//
//                    bool isRed = colorJ == 0;
//
//                    if (currentBoard.checkValidMove(i, isRed)) {
//                        Board nextBoard = currentBoard.copy();
//                        nextBoard.play(i, isRed);
//                        nextBoard.nextPlayer();
//                        *acc = *acc + 1;
//
//                        bestMove = max(bestMove,
//                                       minmax_alphaBeta(nextBoard, false, depth + 1, depthMax, acc, isJ1, alpha, beta));
//
//                        alpha = max(alpha, bestMove);
//                        if (bestMove >= beta) {
//                            break;
//                        }
//                    }
//                }
//            }
//        } else {
//            bestMove = 100;
//            for (int i = 0; i < SIZE; i++) {
//                for (int colorJ = 0; colorJ < 2; colorJ++) {
//
//
//                    bool isRed = colorJ == 0;
//
//                    if (currentBoard.checkValidMove(i, isRed)) {
//                        Board nextBoard = currentBoard.copy();
//                        nextBoard.play(i, isRed);
//                        nextBoard.nextPlayer();
//                        *acc = *acc + 1;
//
//
//                        bestMove = min(bestMove,
//                                       minmax_alphaBeta(nextBoard, true, depth + 1, depthMax, acc, isJ1, alpha, beta));
//
//                        beta = min(beta, bestMove);
//                        if (bestMove <= alpha) {
//                            break;
//                        }
//                    }
//                }
//            }
//        }
//    }


    return bestMove;
}

int DylIA::evaluateDepth(Board board, bool isJ1, int depthMax) {
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
        depth = depthMax + 5;
    } else if (nbMoves <= 3 && board.getNbSeeds() < 20) {
        depth = depthMax + 4;
    } else if (nbMoves <= 4 && board.getNbSeeds() < 25) {
        depth = depthMax + 3;
    } else if (nbMoves <= 6 && board.getNbSeeds() < 35) {
        depth = depthMax + 2;
    } else if (nbMoves <= 6 && board.getNbSeeds() < 40) {
        depth = depthMax + 1;
    } else if (nbMoves <= 7 && board.getNbSeeds() < 35) {
        depth = depthMax + 1;
    } else if (nbMoves <= 10 && board.getNbSeeds() < 55) {
        depth = depthMax;
    } else { // > 14
        depth = depthMax - 1;
    }
    return depth;
}
