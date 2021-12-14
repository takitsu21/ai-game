//
// Created by Dylann on 13/12/2021.
//

#ifndef AI_GAME_DYLIA_H
#define AI_GAME_DYLIA_H
#include "BaseIA.h"

class DylIA : public BaseIA {
public:
    DylIA();
    ~DylIA();
    int evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) override;
    int minmax_alphaBeta(Board &currentBoard, bool AIPlaying, int depth, int depthMax,
                         long long int *acc, bool isJ1, int alpha, int beta) override;
    int evaluateDepth(Board board, bool isJ1, int depthMax) override;
};

#endif //AI_GAME_DYLIA_H
