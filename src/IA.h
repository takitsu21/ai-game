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

using namespace std;

int maxFromArrayPtr(array<int*, TAB_VALUES_SIZE> tabValues);

#endif //AI_GAME_IA_H
