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


void loop(Board board) {

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
    loop(board);
    return EXIT_SUCCESS;
}
