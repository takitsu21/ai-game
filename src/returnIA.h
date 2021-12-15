//
// Created by Dylann on 15/12/2021.
//

#ifndef AI_GAME_RETURNIA_H
#define AI_GAME_RETURNIA_H


#include "DylIA.h"

class returnIA : public DylIA {
    int evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) override;
};


#endif //AI_GAME_RETURNIA_H
