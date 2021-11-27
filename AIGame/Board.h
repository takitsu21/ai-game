#pragma once

// on verra si c'est nécessaire d'utiliser une class ou plutot une struct en terme de perf
class Board
{
private:
	int casePlayer[6];
	int caseOrdi[6];

	bool isAIPlaying;
	int playerPieces;
	int AIPieces;

public:
	Board() {
		
	}
	~Board() {
	}
	
	int* getCasePlayer() {
		return casePlayer;
	}

	int minMax(Board currentBoard, int depth, int depthMax);
};
