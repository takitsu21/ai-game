//
// Created by antoi on 08/12/2021.
//

#ifndef AI_GAME_IA_H
#define AI_GAME_IA_H

#pragma once
#define TAB_VALUES_SIZE 32

#include "Board.h"

using namespace std;

int maxFromArray(const int *tabValues);
int minFromArray(const int *tabValues);
int negamax(Board &currentBoard, bool AIPlaying, int depth, int depthMax, int alpha, int beta, long long *acc, bool isJ1);


#endif //AI_GAME_IA_H
