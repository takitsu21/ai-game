#ifndef BOARD_H

#include <iostream>
#include "case.h"

#pragma once
#define SIZE 16
#define MAX_SEEDS 64

class Board {
private:
    int caseJ2[SIZE];
    int caseJ1[SIZE];

    bool isJ1Turn;
    int J2Pieces;
    int J1Pieces;

public:
    Board();

    ~Board();

    void printCases();

    Case *getBoardCase();

    bool getIsJ1Turn();

    void addPieces(int pieces);

    int evaluate(bool AIPlaying) const;

    bool play(int move, bool isRed);

    bool isEnd();

    int *switchPlayer(bool *isCaseJ1);

    void setNextPlayer();

    static bool checkValidMove(const int* currentCase, int move);

    void eatSeeds(int index);

    void nextPlayer();

    int getNbJ1Seeds() const;

    int getNbJ2Seeds() const;

    int getNbJ1Pieces() const;

    int getNbJ2Pieces() const;

    Board copy();
};

#endif