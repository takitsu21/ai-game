//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
#include <iostream>
#include "src/Board.h"
#include <ctime>
#include <string>
#define TAB_VALUES_SIZE 32

using namespace std;

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

void printTab(int *tab) {
    for (int i = 0; i < TAB_VALUES_SIZE; i++) {
        printf(" [%d] ", tab[i]);
    }
    printf("\n\n\n------------------------------------\n\n\n");
}

int minMax(Board currentBoard, bool AIPlaying, int depth, int depthMax, long long* acc) {
    int tabValues[TAB_VALUES_SIZE];
    *acc = *acc + 1;

    if (currentBoard.isEnd()) {
        if (!AIPlaying) {
            return -33;
        } else {
            return 33;
        }
    }
    if (depth == depthMax) {
        return currentBoard.evaluate(AIPlaying);
    }

    for (int i = 0; i < SIZE; i++) {
        for (int color = 0; color < 2; color++) {
            Board nextBoard = currentBoard.copy();
            bool color_bool = color == 0;

            if (nextBoard.checkValidMove(i, color_bool)) {
                if (nextBoard.play(i, color_bool)) {
                    nextBoard.nextPlayer();
                }

//            printf("\n\n\n---------------------------\n\n\n");
//            printf("depth = %d, move = %d\n", depth, i);
//            nextBoard.printCases();
//            printf("\n\n\n---------------------------\n\n\n");
                int move = minMax(nextBoard, !AIPlaying, depth + 1, depthMax, acc);

                if (color_bool) { // if red tabvalues < 16
                    tabValues[i] = move;
                } else { // if blue tabvalues >= 16
                    tabValues[i + SIZE] = move;
                }

            } else {
                if (AIPlaying) {
                    if (color_bool) { // if red tabvalues < 16
                        tabValues[i] = -100;
                    } else { // if blue tabvalues >= 16
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
//    printf("\n depth %d\n", depth);
//    printTab(tabValues, TAB_VALUES_SIZE);
    return res;
}


//int minMaxAlphaBeta(Board currentBoard, bool AIPlaying, int depth, int depthMax, long long* acc) {
//    int *currentCase;
//    int tabValues[SIZE];
//    *acc = *acc + 1;
//    if (currentBoard.isEnd()) {
//        if (!AIPlaying) {
//            return -25;
//        } else {
//            return 25;
//        }
//    }
//    if (depth == depthMax) {
//        return currentBoard.evaluate();
//    }
//    if (AIPlaying) {
//        currentCase = currentBoard.getCaseJ1();
//    } else {
//        currentCase = currentBoard.getCaseJ2();
//    }
//
//
//    for (int i = 0; i < SIZE; i++) {
//        Board nextBoard = currentBoard.copy();
//        if (Board::checkValidMove(currentCase, i)) {
//            if (nextBoard.play(i)) {
//                nextBoard.setNextPlayer();
//            }
////            printf("\n\n\n---------------------------\n\n\n");
////            printf("depth = %d, move = %d\n", depth, i);
////            nextBoard.printCases();
////            printf("\n\n\n---------------------------\n\n\n");
//            tabValues[i] = minMax(nextBoard, !AIPlaying, depth + 1, depthMax, acc);
//        } else {
//            if (AIPlaying) {
//                tabValues[i] = -100;
//            } else {
//                tabValues[i] = 100;
//            }
//        }
//    }
//
//    int res;
//    if (AIPlaying) {
////        printf("\nTABVALUE MAX: ");
////        printTab(tabValues);
//        res = maxFromArray(tabValues);
//    } else {
////        printf("\nTABVALUE MIN: ");
////        printTab(tabValues);
//        res = minFromArray(tabValues);
//    }
//    return res;
//}


string inputPlayer(bool isJ1) {
    if (isJ1) {
        printf("\n\nJ1 : ");
    } else {
        printf("\n\nJ2 : ");
    }
    string s;
    getline(cin, s);
    return s;
}

pair<int, bool> parse(string s) {
    char color = s.back();
    int x;
    bool isRed;
    if (color == 'B' || color == 'b') {
        isRed = false;
    } else if (color == 'R' || color == 'r') {
        isRed = true;
    } else {
        return make_pair(-1, color);
    }

    try {
        x = stoi(s);
    } catch (const exception& ignored) {
//         ignored.what();
    }

    if (x < 1 || x > SIZE) {
        return make_pair(-1, color);
    }

    return make_pair(x - 1, isRed); // tab index from 0 to 15
}

void winner(Board board) {
    // famine
    printf("j1 seeds %d\n", board.getNbJ1Seeds());
    printf("j2 seeds %d\n", board.getNbJ2Seeds());
    printf("J1 PIECES %d\n", board.getNbJ1Pieces());
    printf("J2 PIECES %d\n", board.getNbJ2Pieces());
    if (board.getNbJ1Seeds() == 0) {
        printf("J2 WIN\n");
    } else if (board.getNbJ2Seeds() == 0) {
        printf("J1 WIN\n");
    }
        // nb pièces
    else if (board.getNbJ1Pieces() > 32) {
        printf("J1 WIN\n");
    } else if (board.getNbJ2Pieces() > 32) {
        printf("J2 WIN\n");
    } else if (board.getNbJ1Pieces() == 32 && board.getNbJ2Pieces() == 32) {
        printf("DRAW\n");
    } else {
        printf("win ??");
    }
}

void gameLoop(Board board) {
    while (!board.isEnd()) {
        board.printCases();
        int x;
        bool isRed;
        bool validMove;

        if (board.getIsJ1Turn()) {
            // JOUEUR HUMAIN
//            string s = inputPlayer(board.getIsJ1Turn());
//            pair<int, bool> res = parse(s);
//            x = res.first;
//            isRed = res.second;

            // JOUEUR IA
            long long acc = 0;
            clock_t time_req = clock();
            x = minMax(board, true, 0, 6, &acc);
            if (x < SIZE) {
                isRed = true;
                printf("\n\nJ1 IA minMax : joue la case %dR, nb noeuds parcouru = %lld en %.3f seconds\n\n", x+1, acc,
                       (float)(clock() - time_req)/CLOCKS_PER_SEC);
            } else {
                isRed = false;
                x -= SIZE;
                printf("\n\nJ1 IA minMax : joue la case %dB, nb noeuds parcouru = %lld en %.3f seconds\n\n", x+1, acc,
                       (float)(clock() - time_req)/CLOCKS_PER_SEC);
            }

        } else {
//            string s = inputPlayer(board.getIsJ1Turn());
//            pair<int, bool> res = parse(s);
//            x = res.first;
//            isRed = res.second;
            long long acc = 0;
            clock_t time_req = clock();
            x = minMax(board, true, 0, 2, &acc);
            if (x < SIZE) {
                isRed = true;
                printf("\n\nJ2 IA minMax : joue la case %dR, nb noeuds parcouru = %lld en %.3f seconds\n\n", x+1, acc,
                       (float)(clock() - time_req)/CLOCKS_PER_SEC);
            } else {
                isRed = false;
                x -= SIZE;
                printf("\n\nJ2 IA minMax : joue la case %dB, nb noeuds parcouru = %lld en %.3f seconds\n\n", x+1, acc,
                       (float)(clock() - time_req)/CLOCKS_PER_SEC);
            }
        }
        if (x == -1) {
            cout << "Coup invalide !" << endl;
            continue;
        }
        validMove = board.play(x, isRed);
        if (validMove) {
            board.nextPlayer();
        }
    }
    board.printCases(); // etat final du jeu
    printf("\n");

    winner(board);
}



//int alphaBetaValue(Board currentBoard, bool AIPlaying, int alpha, int beta, bool isMax, int depthMax) {
//    int* currentCase;
//    if (currentBoard.isEnd()) {
//        if (!AIPlaying) {
//            return -25;
//        } else {
//            return 25;
//        }
//    }
//    // draw position on renvoie 0
//    if (depthMax == 0) {
//        return currentBoard.evaluate();
//    }
//    if (AIPlaying) {
//        currentCase = currentBoard.getCaseJ1();
//    } else {
//        currentCase = currentBoard.getCaseJ2();
//    }
//    if (isMax) {
//        for (int i = 0; i < SIZE;i++) {
//            Board nextBoard = currentBoard.copy();
//            if (Board::checkValidMove(currentCase, i)) {
//                if (nextBoard.play(i)) {
//                    nextBoard.setNextPlayer();
//                    alpha = max(alpha,
//                                alphaBetaValue(nextBoard,
//                                               !AIPlaying, alpha, beta, !isMax,depthMax - 1));
//                    if (alpha >= beta) {
//                        return alpha;
//                    }
//                }
//            }
//        }
//        return alpha;
//    } else {
//        for (int i = 0; i < SIZE; i++) {
//            Board nextBoard = currentBoard.copy();
//            if (Board::checkValidMove(currentCase, i)) {
//                if (nextBoard.play(i)) {
//                    nextBoard.setNextPlayer();
//                    beta = min(beta,
//                               alphaBetaValue(
//                                       nextBoard, !AIPlaying, alpha, beta, !isMax, depthMax - 1));
//                    if (beta <= alpha) {
//                        return beta;
//                    }
//                }
//            }
//        }
//        return beta;
//    }
//
//}

//int decisionAlphaBeta(Board currentBoard, bool AIPlaying, int depthMax) {
//    int* currentCase;
//    int alpha = -25;
//    if (AIPlaying) {
//        currentCase = currentBoard.getCaseJ1();
//    } else {
//        currentCase = currentBoard.getCaseJ2();
//    }
//    int action;
//    for (int i = 0; i < SIZE; i++) {
//        Board nextBoard = currentBoard.copy();
//        if (Board::checkValidMove(currentCase, i)) {
//            if (nextBoard.play(i)) {
//                nextBoard.setNextPlayer();
//                int val = alphaBetaValue(nextBoard, AIPlaying, alpha, 25, false, 10);
//                if (val > alpha) {
//                    action = i;
//                    alpha = val;
//                }
//            }
//        }
//        return action;
//    }
//    return 0;
//}



int main() {
    Board board = Board();
    gameLoop(board);
    return EXIT_SUCCESS;
}
