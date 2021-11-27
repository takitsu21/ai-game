#ifndef BOARD_H
#include <iostream>
#pragma once
#define SIZE 6


// on verra si c'est nécessaire d'utiliser une class ou plutot une struct en terme de perf
class Board
{
private:
	int caseJ2[SIZE];
	int caseJ1[SIZE];

	bool isJ1;
	int J2Pieces;
	int J1Pieces;

public:
	Board();
	~Board();
	void printCases();
	int* getCaseJ2();
	int* getCaseJ1();
	bool getIsJ1();
	void setIsJ1(bool isJ1);
	int minMax(Board currentBoard, int depth, int depthMax);
	int evaluate();
	void play(int coup);
	bool isEnd();
	int* switchPlayer(bool* isCaseJ1);
	void setNextPlayer();
};

#endif