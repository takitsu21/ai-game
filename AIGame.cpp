#include <iostream>
#include "Board.h"

using namespace std;

int maxFromArray(const int* tabValues) {
    int max = -100;
    int idx = 0;
    for (int i = 0; i < SIZE; i++) {
        if (tabValues[i] > max) {
            max = tabValues[i];
            idx = i;
        }
    }
    return idx;
}

int minFromArray(const int* tabValues) {
    int min = 100;
    int idx = 0;
    for (int i = 0; i < SIZE; i++) {
        if (tabValues[i] < min) {
            min = tabValues[i];
            idx = i;
        }
    }
    return idx;
}

void printTab(int* tab) {
    for (int i = 0; i < SIZE; i++) {
        printf(" [%d] ", tab[i]);
    }
    printf("\n");
}

int minMax(Board currentBoard, bool AIPlaying, int depth, int depthMax) {
    int *currentCase;
    int tabValues[SIZE];
    if (currentBoard.isEnd()) {
        if (!AIPlaying) {
            return -25;
        } else {
            return 25;
        }
    }
    if (depth == depthMax) {
        return currentBoard.evaluate();
    }
    if (AIPlaying) {
        currentCase = currentBoard.getCaseJ1();
    } else {
        currentCase = currentBoard.getCaseJ2();
    }


    for (int i = 0; i < SIZE; i++) {
        Board nextBoard = currentBoard.copy();
        if (Board::checkValidMove(currentCase, i)) {
            if (nextBoard.play(i)) {
                nextBoard.setNextPlayer();
            }
//            printf("\n\n\n---------------------------\n\n\n");
//            printf("depth = %d, move = %d\n", depth, i);
//            nextBoard.printCases();
//            printf("\n\n\n---------------------------\n\n\n");
            tabValues[i] = minMax(nextBoard, !AIPlaying, depth + 1, depthMax);
        } else {
            if (AIPlaying) {
                tabValues[i] = -100;
            } else {
                tabValues[i] = 100;
            }
        }
    }

    int res;
    if (AIPlaying) {
//        printf("\nTABVALUE MAX: ");
//        printTab(tabValues);
        res = maxFromArray(tabValues);
    } else {
//        printf("\nTABVALUE MIN: ");
//        printTab(tabValues);
        res = minFromArray(tabValues);
    }
    return res;
}


int inputPlayer(bool isJ1) {
    if (isJ1) {
        printf("\n\nJ1 : ");
    } else {
        printf("\n\nJ2 : ");
    }
    int x;
    cin >> x;
    return x;
}


void gameLoop(Board board) {
    while (!board.isEnd()) {
        board.printCases();
        int x;
        bool validMove;
        if (board.getIsJ1()) {
            x = minMax(board, board.getIsJ1(), 0, 7);
            printf("\n\nJ1 IA minMax : %d\n\n", x);
        }
        else {
            x = inputPlayer(board.getIsJ1());
            printf("\n\nJ2 IA minMax : %d\n\n", x);
        }
        validMove = board.play(x);
        if (validMove) {
            board.setNextPlayer();
        } else {
            printf("INVALID !");
        }
    }

    if (board.getIsJ1()) {
        printf("J2 win\n");
    } else {
        printf("J1 win\n");
    }
}


int main() {
    Board board = Board();
    gameLoop(board);
    return EXIT_SUCCESS;
}
