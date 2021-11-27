#ifndef BOARD_H

#include <iostream>

#pragma once
#define SIZE 6


// on verra si c'est n�cessaire d'utiliser une class ou plutot une struct en terme de perf
class Board {
private:
    int caseJ2[SIZE];
    int caseJ1[SIZE];

    bool isJ1;
    int J2Pieces;
    int J1Pieces;

public:
    Board();

    ~Board();

    void printCases();

    int *getCaseJ2();

    int *getCaseJ1();

    bool getIsJ1();

    void addPieces(int pieces);

    void setIsJ1(bool isJ1);

    int minMax(Board currentBoard, int depth, int depthMax);

    int evaluate();

    bool play(int move);

    bool isEnd();

    int *switchPlayer(bool *isCaseJ1);

    void setNextPlayer();

    static bool checkValidMove(const int* currentCase, int move);

    void eatSeeds(int index, int* currentCase, bool isCaseJ1);
};

#endif