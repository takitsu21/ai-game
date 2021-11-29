#include "Board.h"

bool isEmpty(const int* currentCase) {
    for (int i = 0; i < SIZE; i++) {
        if (currentCase[i] != 0) {
            return false;
        }
    }
    return true;
}


int Board::minMax(Board currentBoard, int depth, int depthMax) {
    return 0;
}

Board::Board() {
    for (int i = 0; i < SIZE; i++) {
        caseJ1[i] = 4;
        caseJ2[i] = 4;
    }
    isJ1 = true;
    J2Pieces = 0;
    J1Pieces = 0;

}

Board Board::copy() {
    Board b = Board();
    for (int i = 0; i < SIZE; i++) {
        b.caseJ1[i] = caseJ1[i];
        b.caseJ2[i] = caseJ2[i];
    }
    b.isJ1 = isJ1;
    b.J2Pieces = J2Pieces;
    b.J1Pieces = J1Pieces;

    return b;
}

Board::~Board() {

}

int *Board::getCaseJ2() {
    return caseJ2;
}

int *Board::getCaseJ1() {
    return caseJ1;
}

void Board::printCases() {
    printf("\n\n Nouveau tour: \n");

    printf("pieces J1 : %d, pieces J2 : %d\n\n", J1Pieces, J2Pieces);
    printf("J2 ");
    for (int i = SIZE - 1; i >= 0; i--) {
        printf("|%d|-", caseJ2[i]);
    }
    printf("\nNp ");
    for (int i = SIZE - 1; i >= 0; i--) {
        printf(" %d  ", i);
    }
    printf("\n\n");
    printf("J1 ");
    for (int i = 0; i < SIZE; i++) {
        printf("|%d|-", caseJ1[i]);
    }
    printf("\nNp ");
    for (int i = 0; i < SIZE; i++) {
        printf(" %d  ", i);
    }
}


bool Board::getIsJ1() {
    return isJ1;
}


bool Board::play(int move) {
    int seeds;
    int *currentCase;
    bool isCaseJ1;

    if (isJ1) {
        seeds = caseJ1[move];
        currentCase = getCaseJ1();
        isCaseJ1 = true;
    } else {
        seeds = caseJ2[move];
        currentCase = getCaseJ2();
        isCaseJ1 = false;
    }

    if (!checkValidMove(currentCase, move)) {
        //printf("Coup invalide\n");
        return false;
    }

    int index = move;
    currentCase[move] = 0;
    int index = move;

    while (seeds > 0) {
        if (index >= SIZE - 1) {
            index = 0;
            currentCase = switchPlayer(&isCaseJ1);
        } else {
            index++;
        }

        if (index == move && ((isCaseJ1 == getIsJ1()) || (!isCaseJ1 && !getIsJ1()))) {
            continue;
        } else {
            currentCase[index]++;
            seeds--;
        }
    }

    eatSeeds(index, currentCase, isCaseJ1);
    return true;
}


int *Board::switchPlayer(bool *isCaseJ1) {

    if (*isCaseJ1) {
        *isCaseJ1 = !(*isCaseJ1);
        return getCaseJ2();
    } else {
        *isCaseJ1 = !(*isCaseJ1);
        return getCaseJ1();
    }
}


bool Board::isEnd() {
    if (isJ1) {
        return J1Pieces >= 25 || isEmpty(caseJ2);
    }
    return J2Pieces >= 25 || isEmpty(caseJ1);
}


void Board::setNextPlayer() {
    isJ1 = !isJ1;
}


bool Board::checkValidMove(const int *currentCase, int move) {
    return currentCase[move] > 0 && move >= 0 && move <= 5;
}


void Board::eatSeeds(int index, int *currentCase, bool isCaseJ1) {
    if (getIsJ1() == isCaseJ1) {
        return;
    }
    while (index >= 0) {
        if (currentCase[index] == 2 || currentCase[index] == 3) {
            addPieces(currentCase[index]);
            currentCase[index] = 0;
        } else {
            break;
        }
        index--;
    }
}


void Board::addPieces(int pieces) {
    if (isJ1) {
        J1Pieces += pieces;
    } else {
        J2Pieces += pieces;
    }
}