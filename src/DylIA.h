//
// Created by Dylann on 13/12/2021.
//

#ifndef AI_GAME_DYLIA_H
#define AI_GAME_DYLIA_H
#include "BaseIA.h"

class DylIA : public AbstractIA {
public:
    DylIA();
    ~DylIA();
    int evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) override;
};

#endif //AI_GAME_DYLIA_H
