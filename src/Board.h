#ifndef BOARD_H

#include <iostream>

#pragma once
#define SIZE 16
#define MAX_SEEDS 64

class Board {
private:

    int redCase[SIZE];
    int blueCase[SIZE];
    bool isJ1Case[SIZE];

    //Case boardCase[SIZE]; //J1 PAIR dans le CODE, mais IMPAIR dans le print !!!!!!

    bool isJ1Turn;
    int J2Pieces;
    int J1Pieces;
    int nbSeeds;
    int nbJ1Seeds;
    int nbJ2Seeds;
public:

    int nbJ1RedSeeds;
    int nbJ2RedSeeds;
    int nbJ1BlueSeeds;
    int nbJ2BlueSeeds;

    Board();
    explicit Board(bool test);
    Board(const Board& board);

    ~Board();

    void printCases();

    bool getIsJ1Turn() const;

    void addPieces(int pieces);

    int evaluate(bool isJ1, bool AIPlaying, int depth, int depthMax) const;

    void play(int move, bool isRed);

    bool isEnd(bool isJ1) const;

    bool checkValidMove(int move, bool isRed);

    void eatSeeds(int index);

    void nextPlayer();

    int getNbJ1Seeds() const;

    int getNbJ2Seeds() const;

    int getNbJ1Pieces() const;

    int getNbJ2Pieces() const;

    int getNbSeeds() const;

    Board copy();

};

#endif