//
// Created by antoi on 12/12/2021.
//

#ifndef AI_GAME_ABSTRACTIA_H
#define AI_GAME_ABSTRACTIA_H

#include "Board.h"
#include "IA.h"

class AbstractIA {
public:
    AbstractIA() = default;
    ~AbstractIA() = default;

    virtual int start(Board &currentBoard, bool AIPlaying, int depth, int depthMax,
                      long long *acc, bool isJ1) = 0;

    virtual int evaluateDepth(Board board, bool isJ1, int depthMax) = 0;


    virtual void minmax_alphaBetaThread(Board currentBoard, bool AIPlaying, int depth, int depthMax,
                                        long long *acc, bool isJ1, int *res) = 0;

    virtual int minmax_alphaBeta(Board &currentBoard, bool AIPlaying, int depth, int depthMax,
                                 long long *acc, bool isJ1, int alpha,int beta) = 0;

    virtual int evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) = 0;
};


#endif //AI_GAME_ABSTRACTIA_H
