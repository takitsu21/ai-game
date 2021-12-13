//
// Created by antoi on 13/12/2021.
//

#ifndef AI_GAME_ANTIA1_H
#define AI_GAME_ANTIA1_H


#include "BaseIA.h"

class AntIA1 : public BaseIA{
public:
    int evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) override;
};


#endif //AI_GAME_ANTIA1_H
