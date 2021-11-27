#ifndef BOARD_H
#include <iostream>
#pragma once
#define SIZE 6


// on verra si c'est nécessaire d'utiliser une class ou plutot une struct en terme de perf
class Board
{
private:
	int casePlayer[SIZE];
	int caseOrdi[SIZE];

	bool isAIPlaying;
	int playerPieces;
	int AIPieces;

public:
	Board();
	~Board();
	void printCases();
	int* getCasePlayer();
	int minMax(Board currentBoard, int depth, int depthMax);
	int evaluate();
};

#endif