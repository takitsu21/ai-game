//
// Created by Dylann on 13/12/2021.
//

#include "QuiesceIA.h"
#include "IA.h"


int QuiesceIA::evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) {
    int nbJ2Seeds = board.getNbJ2Seeds();
    int nbJ1Seeds = board.getNbJ1Seeds();
    int J2Pieces = board.getNbJ2Pieces();
    int J1Pieces = board.getNbJ1Pieces();
    int nbSeeds = board.getNbSeeds();

    if (isJ1) {
        if (AIPlaying && nbJ2Seeds <= 0) { // on évalue le coup de l'adversaire (J2)
            return -64;
        } else if (J2Pieces > 32) {
            return -64;
        } else if (nbSeeds < 8 && J1Pieces < J2Pieces) {
            return -64;
        } else if (!AIPlaying && nbJ1Seeds <= 0) { // Si on est joueur 2 et qu'on évalue notre propre coup
            return 64 + depthMax - depth;
        } else if (nbSeeds < 8 && J1Pieces > J2Pieces) {
            return 64 + depthMax - depth;
        } else if (J1Pieces > 32) {
            return 64 + depthMax - depth;
        } else {
            int x =  J1Pieces - J2Pieces;

            if (board.getNbSeeds() < 25) {
                // fin de partie
                x += (nbJ1Seeds - nbJ2Seeds) / 10;

            }
            else if (board.getNbSeeds() <= 40) {
                // milieu de partie
                int caseGrenier = 0;
                int maxSeeds = 0;
                for (int i = 0; i < SIZE;i+=2) {
                    int total = board.getCaseRed()[i] + board.getCaseBlue()[i];
                    if (total >= 6) {
                        maxSeeds = total;
                    }
                }
                if (maxSeeds) {
                    x += 2;
                }

            }
            else if (board.getNbSeeds() <= 64) {
                // debut de partie
                int nbAlterne = 0;
                bool isAlternated = false;
                for (int i = 0; i < SIZE;i+=2) {
                    int total = board.getCaseRed()[i] + board.getCaseBlue()[i];
                    int total2 = board.getCaseRed()[i+1] + board.getCaseBlue()[i+1];

                    if (total == 0 && total2 > 0) {
                        nbAlterne++;
                    }
                }
                x += nbAlterne / 2;
            }


//            int maxRed = 0;
//            int maxBlue = 0;
//            if (AIPlaying) {
//                for (int i = 0; i < SIZE; i+=2) {
//                    int red = board.getCaseRed()[i];
//                    int blue = board.getCaseBlue()[i];
//                    if (red > 0) {
//                        int caseToGo = board.getCaseRed()[(i+red)%SIZE];
//                        int total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                        while (total == 2 || total == 3) {
//                            if (caseToGo < 0) {
//                                caseToGo = SIZE - 1;
//                            }
//                            total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                            if (total == 2 || total == 3) {
//                                maxRed += 1;
//                            }
//                            caseToGo--;
//                        }
//
//                    }
//                    if (blue > 0) {
//                        int caseToGo = board.getCaseBlue()[(i+(blue * 2))%SIZE];
//                        int total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                        while (total == 2 || total == 3) {
//                            if (caseToGo < 0) {
//                                caseToGo = SIZE - 1;
//                            }
//                            total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                            if (total == 2 || total == 3) {
//                                maxBlue += 1;
//                            }
//                            caseToGo--;
//                        }
//                    }
//                }
//                int suiteScore = max(maxRed, maxBlue);
//                if (x + suiteScore > 32) {
//                    return 64;
//                } else {
//                    x += suiteScore;
//                }
//            } else {
//                for (int i = 1; i < SIZE; i+=2) {
//                    int red = board.getCaseRed()[i];
//                    int blue = board.getCaseBlue()[i];
//                    if (red > 0) {
//                        int caseToGo = board.getCaseRed()[(i+red)%SIZE];
//                        int total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                        while (total == 2 || total == 3) {
//                            if (caseToGo < 0) {
//                                caseToGo = SIZE - 1;
//                            }
//                            total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                            if (total == 2 || total == 3) {
//                                maxRed -= 1;
//                            }
//                            caseToGo--;
//                        }
//
//                    }
//                    if (blue > 0) {
//                        int caseToGo = board.getCaseBlue()[(i+(blue * 2))%SIZE];
//                        int total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                        while (total == 2 || total == 3) {
//                            if (caseToGo < 0) {
//                                caseToGo = SIZE - 1;
//                            }
//                            total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                            if (total == 2 || total == 3) {
//                                maxBlue -= 1;
//                            }
//                            caseToGo--;
//                        }
//                    }
//                }
//                int suiteScore = min(maxRed, maxBlue);
//                if (x + suiteScore > 32) {
//                    return -64;
//                } else {
//                    x += suiteScore;
//                }
//            }
            return x;
        }
    } else {
        if (AIPlaying && nbJ2Seeds <= 0) { // on évalue le coup de l'adversaire (J2)
            return -64;
        } else if (J1Pieces > 32) {
            return -64;
        } else if (nbSeeds < 8 && J2Pieces < J1Pieces) {
            return -64;
        } else if (!AIPlaying && nbJ1Seeds <= 0) { // Si on est joueur 2 et qu'on évalue notre propre coup
            return 64 + depthMax - depth;
        } else if (nbSeeds < 8 && J2Pieces > J1Pieces) {
            return 64 + depthMax - depth;
        } else if (J2Pieces > 32) {
            return 64 + depthMax - depth;
        } else {
            int x;
            x = J2Pieces - J1Pieces;
            x += (nbJ2Seeds - nbJ1Seeds);
//            int maxRed = 0;
//            int maxBlue = 0;
//            if (AIPlaying) {
//                for (int i = 1; i < SIZE; i+=2) {
//                    int red = board.getCaseRed()[i];
//                    int blue = board.getCaseBlue()[i];
//                    if (red > 0) {
//                        int caseToGo = board.getCaseRed()[(i+red)%SIZE];
//                        int total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                        while (total == 2 || total == 3) {
//                            if (caseToGo < 0) {
//                                caseToGo = SIZE - 1;
//                            }
//                            total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                            if (total == 2 || total == 3) {
//                                maxRed += 1;
//                            }
//                            caseToGo--;
//                        }
//
//                    }
//                    if (blue > 0) {
//                        int caseToGo = board.getCaseBlue()[(i+(blue * 2))%SIZE];
//                        int total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                        while (total == 2 || total == 3) {
//                            if (caseToGo < 0) {
//                                caseToGo = SIZE - 1;
//                            }
//                            total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                            if (total == 2 || total == 3) {
//                                maxBlue += 1;
//                            }
//                            caseToGo--;
//                        }
//                    }
//                }
//                int suiteScore = max(maxRed, maxBlue);
//                if (x + suiteScore > 32) {
//                    return 64;
//                } else {
//                    x += suiteScore;
//                }
//            } else {
//                for (int i = 1; i < SIZE; i+=2) {
//                    int red = board.getCaseRed()[i];
//                    int blue = board.getCaseBlue()[i];
//                    if (red > 0) {
//                        int caseToGo = board.getCaseRed()[(i+red)%SIZE];
//                        int total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                        while (total == 2 || total == 3) {
//                            if (caseToGo < 0) {
//                                caseToGo = SIZE - 1;
//                            }
//                            total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                            if (total == 2 || total == 3) {
//                                maxRed -= 1;
//                            }
//                            caseToGo--;
//                        }
//
//                    }
//                    if (blue > 0) {
//                        int caseToGo = board.getCaseBlue()[(i+(blue * 2))%SIZE];
//                        int total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                        while (total == 2 || total == 3) {
//                            if (caseToGo < 0) {
//                                caseToGo = SIZE - 1;
//                            }
//                            total = board.getCaseRed()[caseToGo] + board.getCaseBlue()[caseToGo];
//                            if (total == 2 || total == 3) {
//                                maxBlue -= 1;
//                            }
//                            caseToGo--;
//                        }
//                    }
//                }
//                int suiteScore = min(maxRed, maxBlue);
//                if (x + suiteScore > 32) {
//                    return -64;
//                } else {
//                    x += suiteScore;
//                }
//            }

            return x;
        }
    }}


int QuiesceIA::evaluateDepth(Board board, bool isJ1, int depthMax) {
    int nbMoves = 0;
    int depth = depthMax;
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
        depth = depthMax + 2;
    } else if (nbMoves <= 7 && board.getNbSeeds() < 30) {
        depth = depthMax + 1;
    }
    else if (nbMoves <= 10 && board.getNbSeeds() < 55) {
        depth = depthMax;
    }
    else { // > 14
        depth = depthMax - 1;
    }
    return depth;
}


void QuiesceIA::minmax_alphaBetaThread(Board currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc,
                                       bool isJ1,
                                       int *res) {
    long long acc2 = 0;
    int score = minmax_alphaBeta(currentBoard, AIPlaying, depth, depthMax, &acc2, isJ1, -100, 100, false);
    *acc = *acc + acc2;
    *res = score;
}

int QuiesceIA::minmax_alphaBeta(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc,
                                bool isJ1, int alpha, int beta, bool isQuiesce) {

    *acc = *acc + 1;

    if (currentBoard.isEnd(isJ1)) {
        return evaluate(currentBoard, isJ1, AIPlaying, depth, depthMax);;
    }
    if (depth == depthMax) {
        if (currentBoard.getNbSeeds() < 35) {
            return quiesce(currentBoard, !AIPlaying, 0, 1, acc, isJ1, alpha, beta);

        } else {
            return evaluate(currentBoard, isJ1, AIPlaying, depth, depthMax);;

        }

    }

    int bestMove;

    array<pair<int, pair<int, bool>>, TAB_VALUES_SIZE> moves{};
//    for (int i = 0; i < SIZE; i++) {
//        for (int colorJ = 0; colorJ < 2; colorJ++) {
//            bool isRed = colorJ == 0;
//            if (currentBoard.checkValidMove(i, isRed)) {
//                int score = evaluate(currentBoard, isJ1, AIPlaying, depth, depthMax);
//                if (isRed) {
//                    moves[i] = make_pair(score,
//                                         make_pair(i, isRed));
//                } else {
//                    moves[i + SIZE] = make_pair(score,
//                                                make_pair(i, isRed));
//                }
//            }
//        }
//    }
//
//    std::sort(std::begin(moves), std::end(moves), myCompare);


    if (AIPlaying) {
        bestMove = -100;
        for (int i = 0; i < TAB_VALUES_SIZE; i++) {
            int x = moves[i].second.first;
            bool isRed = moves[i].second.second;
            if (currentBoard.checkValidMove(x, isRed)) {
                Board nextBoard = currentBoard.copy();
                nextBoard.play(x, isRed);
                nextBoard.nextPlayer();

                bestMove = max(bestMove,
                               minmax_alphaBeta(nextBoard, false, depth + 1, depthMax, acc, isJ1, alpha, beta, false));

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

                bestMove = min(bestMove,
                               minmax_alphaBeta(nextBoard, true, depth + 1, depthMax, acc, isJ1, alpha, beta, false));

                beta = min(beta, bestMove);
                if (bestMove <= alpha) {
                    break;
                }
            }
        }
    }

    return bestMove;
}


int QuiesceIA::quiesce(Board &board, bool AIPlaying, int depth, int depthMax, long long *acc,
                       bool isJ1, int alpha, int beta) {
    *acc = *acc + 1;

    if (board.isEnd(isJ1) || depth == depthMax) {
        int score = evaluate(board, isJ1, AIPlaying, depth, depthMax);
        return score;
    }

    int bestMove;

    array<pair<int, pair<int, bool>>, TAB_VALUES_SIZE> moves{};
//    for (int i = 0; i < SIZE; i++) {
//        for (int colorJ = 0; colorJ < 2; colorJ++) {
//            bool isRed = colorJ == 0;
//            if (board.checkValidMove(i, isRed)) {
//                int score = evaluate(board, isJ1, AIPlaying, depth, depthMax);
//                if (isRed) {
//                    moves[i] = make_pair(score,
//                                         make_pair(i, isRed));
//                } else {
//                    moves[i + SIZE] = make_pair(score,
//                                                make_pair(i, isRed));
//                }
//            }
//        }
//    }
//
//    std::sort(std::begin(moves), std::end(moves), myCompare);

    int standPat = evaluate(board, isJ1, AIPlaying, depth, depthMax);
    if (AIPlaying) {
        bestMove = -100;
        if (standPat >= beta) {
            return standPat;
        } else {
            alpha = standPat;
        }
        for (int i = 0; i < TAB_VALUES_SIZE; i++) {
            int x = moves[i].second.first;
            bool isRed = moves[i].second.second;
            if (board.checkValidMove(x, isRed)) {
                Board nextBoard = board.copy();
                nextBoard.play(x, isRed);
                nextBoard.nextPlayer();

                bestMove = max(bestMove,
                               quiesce(nextBoard, false, depth + 1, depthMax, acc, isJ1, alpha, beta));

                alpha = max(alpha, bestMove);
                if (bestMove >= beta) {
                    break;
                }
            }
        }
    } else {
        bestMove = 100;
        if (standPat <= alpha) {
            return standPat;
        } else {
            beta = standPat;
        }
        for (int i = 0; i < TAB_VALUES_SIZE; i++) {
            int x = moves[i].second.first;
            bool isRed = moves[i].second.second;
            if (board.checkValidMove(x, isRed)) {
                Board nextBoard = board.copy();
                nextBoard.play(x, isRed);
                nextBoard.nextPlayer();

                bestMove = min(bestMove,
                               quiesce(nextBoard, true, depth + 1, depthMax, acc, isJ1, alpha, beta));

                beta = min(beta, bestMove);
                if (bestMove <= alpha) {
                    break;
                }
            }
        }
    }

    return bestMove;
}