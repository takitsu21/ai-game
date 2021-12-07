//#pragma GCC optimize("0fast")
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


void winner(const Board &board) {
    // famine
    printf("j1 seeds %d\n", board.getNbJ1Seeds());
    printf("j2 seeds %d\n", board.getNbJ2Seeds());
    printf("J1 PIECES %d\n", board.getNbJ1Pieces());
    printf("J2 PIECES %d\n", board.getNbJ2Pieces());
    printf("SEEDS %d\n", board.getNbSeeds());
    if (board.getNbJ1Pieces() > 32) {
        printf("J1 WIN\n");
    } else if (board.getNbJ2Pieces() > 32) {
        printf("J2 WIN\n");
    } else if (board.getNbJ1Seeds() == 0) {
        printf("J2 WIN\n");
    } else if (board.getNbJ2Seeds() == 0) {
        printf("J1 WIN\n");
    } else if (board.getNbJ1Pieces() == 32 && board.getNbJ2Pieces() == 32) {
        printf("DRAW\n");
    } else if (board.getNbSeeds() < 8) {
        if (board.getNbJ2Pieces() > board.getNbJ1Pieces()) {
            printf("J2 WIN\n");
        } else if (board.getNbJ2Pieces() < board.getNbJ1Pieces()) {
            printf("J1 WIN\n");
        } else {
            printf("DRAW\n");
        }
    } else {
        printf("win ???\n");
    }
}

int
negamax(Board &currentBoard, bool AIPlaying, int depth, int depthMax, int alpha, int beta, long long *acc, bool isJ1) {
    int tabValues[TAB_VALUES_SIZE];
    *acc = *acc + 1;
//    int score = currentBoard.evaluate(isJ1);
//    if (score == 64) {
//        return score;
//    }
    if (currentBoard.isEnd() || depth == depthMax) {
        int score = currentBoard.evaluate(isJ1);

        if (AIPlaying) {
            return 1 * (score - depth);
        } else {
            return -1 * (score + depth);
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
                                                  -beta, -alpha, acc, isJ1));
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
    } catch (const exception &ignored) {
//         ignored.what();
    }

    if (x < 1 || x > SIZE) {
        return make_pair(-1, color);
    }

    return make_pair(x - 1, isRed); // tab index from 0 to 15
}


void gameLoop(Board board) {
    int nbTour = 0;
    while (!board.isEnd()) {
        printf("TOUR NUM: %d\n", nbTour);
        nbTour++;
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
            x = negamax(board, true, 0, 1, -100, 100, &acc, true);
            if (x < SIZE) {
                isRed = true;
                printf("\n\nJ1 IA negamax : joue la case %dR, nb noeuds parcouru = %lld en %.3f seconds\n\n", x + 1,
                       acc,
                       (float) (clock() - time_req) / CLOCKS_PER_SEC);
            } else {
                isRed = false;
                x -= SIZE;
                printf("\n\nJ1 IA negamax : joue la case %dB, nb noeuds parcouru = %lld en %.3f seconds\n\n", x + 1,
                       acc,
                       (float) (clock() - time_req) / CLOCKS_PER_SEC);
            }

        } else {
//            string s = inputPlayer(board.getIsJ1Turn());
//            pair<int, bool> res = parse(s);
//            x = res.first;
//            isRed = res.second;
            long long acc = 0;
            clock_t time_req = clock();
            x = negamax(board, true, 0, 7, -100, 100, &acc, false);
            if (x < SIZE) {
                isRed = true;
                printf("\n\nJ2 IA negamax : joue la case %dR, nb noeuds parcouru = %lld en %.3f seconds\n\n", x + 1,
                       acc,
                       (float) (clock() - time_req) / CLOCKS_PER_SEC);
            } else {
                isRed = false;
                x -= SIZE;
                printf("\n\nJ2 IA negamax : joue la case %dB, nb noeuds parcouru = %lld en %.3f seconds\n\n", x + 1,
                       acc,
                       (float) (clock() - time_req) / CLOCKS_PER_SEC);
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

int main() {
    Board board = Board();
    gameLoop(board);
    return EXIT_SUCCESS;
}
