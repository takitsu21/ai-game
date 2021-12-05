cmake_minimum_required(VERSION 3.21)
project(ai_game)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ai_game
        AIGame.cpp
        src/Board.cpp
        src/Board.h)
