//
// Created by antoi on 08/12/2021.
//

#ifndef AI_GAME_IA_H
#define AI_GAME_IA_H

#pragma once
#define TAB_VALUES_SIZE 32

#include "Board.h"
#include <array>
#include <thread>
#include <utility>
#include <algorithm>
#include <iterator>

using namespace std;

int maxFromArrayPtr(array<int*, TAB_VALUES_SIZE> tabValues);
int quiesce(Board board, int alpha, int beta, bool AIPlaying, bool isJ1, int depth, int depthMax);
bool myCompare(const std::pair<int, pair<int, bool>> &p1, const std::pair<int, pair<int, bool>> &p2);
#endif //AI_GAME_IA_H
