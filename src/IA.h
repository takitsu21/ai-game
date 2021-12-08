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
//int negamax(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc, bool isJ1, bool firstCall);
int negamaxStart(Board &currentBoard, bool AIPlaying, int depth, int depthMax, long long *acc, bool isJ1, bool firstCall);
int evaluateDepth(Board board, bool isJ1, int depthMax);


#endif //AI_GAME_IA_H
