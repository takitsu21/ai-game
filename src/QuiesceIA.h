//
// Created by Dylann on 13/12/2021.
//

#ifndef AI_GAME_QUIESCEIA_H
#define AI_GAME_QUIESCEIA_H
#include "BaseIA.h"


class QuiesceIA : public BaseIA  {
public:
    int minmax_alphaBeta(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc, bool isJ1, int alpha, int beta) override;
    int quiesce(Board board, int alpha, int beta, bool AIPlaying, bool isJ1, int depth, int depthMax);
    int evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) override;
};


#endif //AI_GAME_QUIESCEIA_H
