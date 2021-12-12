//
// Created by antoi on 12/12/2021.
//

#ifndef AI_GAME_BASEIA_H
#define AI_GAME_BASEIA_H

#include "AbstractIA.h"

class BaseIA : public AbstractIA {
public:
    BaseIA() = default;
    ~BaseIA() override = default;
    int start(Board &currentBoard, bool AIPlaying, int depth, int depthMax,
              long long int *acc, bool isJ1) override;
    int evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) override;

private:


    int evaluateDepth(Board board, bool isJ1, int depthMax) override;

    int minmax_alphaBeta(Board &currentBoard, bool AIPlaying, int depth, int depthMax,
                         long long int *acc, bool isJ1, int alpha, int beta) override;

    void minmax_alphaBetaThread(Board currentBoard, bool AIPlaying, int depth, int depthMax,
                                long long int *acc, bool isJ1, int *res) override;


};

#endif //AI_GAME_BASEIA_H
