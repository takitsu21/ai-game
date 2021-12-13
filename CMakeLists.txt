cmake_minimum_required(VERSION 3.18)
project(ai_game)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

include_directories(.)

find_package(Threads REQUIRED)

add_executable(ai_game
        AIGame.cpp
        src/Board.cpp
        src/Board.h
        src/IA.cpp
        src/IA.h src/BaseIA.cpp src/AbstractIA.h src/BaseIA.h src/QuiesceIA.cpp src/QuiesceIA.h)

target_link_libraries(ai_game Threads::Threads)
