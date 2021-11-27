#include "Board.h"
int Board::minMax(Board currentBoard, int depth, int depthMax) {

}

Board::Board() {
	for (int i = 0; i < sizeof(casePlayer) / sizeof(*casePlayer); i++) {
		caseOrdi[0] = 4;
		casePlayer[0] = 4;
	}
	isAIPlaying = false;
	playerPieces = 0;
	AIPieces = 0;

}