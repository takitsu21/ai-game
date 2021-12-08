# cmake_minimum_required(VERSION <specify CMake version here>)
project(ai_game)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ai_game
        AIGame.cpp
        src/Board.cpp
        src/Board.h
        src/IA.cpp
        src/IA.h)
