//
// Created by Dylann on 13/12/2021.
//

#include "QuiesceIA.h"
#include "IA.h"


int QuiesceIA::evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) {
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
        }
        else if (J2Pieces > 32) {
            return -64;
        } else if (J1Pieces > 32) {
            x = 64;
        } else if (nbSeeds < 8 && J1Pieces < J2Pieces) {
            return -64;
        } else if (nbSeeds < 8 && J1Pieces > J2Pieces) {
            x = 64;
        } else {
            x = J1Pieces - J2Pieces;
        }

        x += (nbJ1Seeds - nbJ2Seeds) / 10;
        if (x < 0 && nbJ1Seeds <= 3) {
            return -64;
        }
    } else {
        if (!AIPlaying && nbJ1Seeds <= 0 && J1Pieces < 33) { // Si on est joueur 2 et qu'on évalue notre propre coup
            x = 64;
        }
        else if (!AIPlaying && nbJ2Seeds <= 0 && J2Pieces > 32) {
            x = 64;
        }
        else if (AIPlaying && nbJ1Seeds <= 0 && J1Pieces > 32) {
            return -64;
        }
        else if (AIPlaying && nbJ2Seeds <= 0) {
            return -64;
        }
        else if (J1Pieces > 32) {
            return -64;
        } else if (J2Pieces > 32) {
            x = 64;
        } else if (nbSeeds < 8 && J2Pieces < J1Pieces) {
            return -64;
        } else if (nbSeeds < 8 && J2Pieces > J1Pieces) {
            x = 64;
        } else {
            x = J2Pieces - J1Pieces;
        }

        x += (nbJ2Seeds - nbJ1Seeds) / 10;
        if (x < 0 && nbJ2Seeds <= 3) {
            return -64;
        }

    }
    x += depthMax - depth;
    return x;

}



int QuiesceIA::minmax_alphaBeta(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc,
                                bool isJ1, int alpha, int beta) {


    if (currentBoard.isEnd(isJ1)) {
        int score = evaluate(currentBoard, isJ1, AIPlaying, depth, depthMax);
        return score;
    }
    if (depth == depthMax) {
        return quiesce(currentBoard, alpha, beta, AIPlaying, isJ1, depthMax, depthMax + 2);
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

    return bestMove;
}


int QuiesceIA::quiesce(Board board, int alpha, int beta, bool AIPlaying, bool isJ1, int depth, int depthMax) {
    int standPat = evaluate(board, isJ1, AIPlaying, depth, depthMax);
//    printf("quiesce\n");
    if (standPat >= beta) {
        return beta;
    }
    if (alpha < standPat) {
        alpha = standPat;
    }
    if (depthMax == depth) {
        return standPat;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int color = 0; color < 2; color++) {
            bool isRed = color == 0;
            if (board.checkValidMove(i, isRed)) {
                Board nextBoard = board.copy();
                nextBoard.play(i, isRed);
                nextBoard.nextPlayer();


                standPat = -quiesce(nextBoard, -beta, -alpha, !AIPlaying, isJ1, depth + 1, depthMax);
                if (standPat >= beta) {
                    return beta;
                }
                if (standPat > alpha) {
                    alpha = standPat;
                }

            }
        }
    }
    return alpha;
}