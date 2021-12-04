#ifndef BOARD_H

#include <iostream>
#include "case.h"

#pragma once
#define SIZE 16
#define MAX_SEEDS 64

class Board {
private:

    Case boardCase[SIZE]; //J1 PAIR dans le CODE, mais IMPAIR dans le print !!!!!!

    bool isJ1Turn;
    int J2Pieces;
    int J1Pieces;
    int nbSeeds;
    int nbJ1Seeds;
    int nbJ2Seeds;

public:
    Board();
    Board(bool test);

    ~Board();

    void printCases();

    Case *getBoardCase();

    bool getIsJ1Turn();

    void addPieces(int pieces);

    int evaluate(bool AIPlaying) const;

    bool play(int move, bool isRed);

    bool isEnd() const;

    bool checkValidMove(int move, bool isRed);

    void eatSeeds(int index);

    void nextPlayer();

    int getNbJ1Seeds() const;

    int getNbJ2Seeds() const;

    int getNbJ1Pieces() const;

    int getNbJ2Pieces() const;

    Board copy();
};

#endif