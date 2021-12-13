//
// Created by Dylann on 13/12/2021.
//

#ifndef AI_GAME_QUIESCEIA_H
#define AI_GAME_QUIESCEIA_H
#include "BaseIA.h"


class QuiesceIA : public BaseIA  {
public:
    int minmax_alphaBeta(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc, bool isJ1, int alpha, int beta) override;
};


#endif //AI_GAME_QUIESCEIA_H
