cmake_minimum_required(VERSION 3.18)
project(ai_game)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

find_package(Threads REQUIRED)

add_executable(
        AIGame.cpp
        src/Board.cpp
        src/Board.h
        src/IA.cpp
        src/IA.h)

target_link_libraries(ai_game Threads::Threads)
