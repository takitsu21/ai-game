#include "Board.h"

int Board::minMax(Board currentBoard, int depth, int depthMax) {
	return 0;
}

Board::Board() {
	for (int i = 0; i < SIZE; i++) {
		caseOrdi[i] = 4;
		casePlayer[i] = 4;
	}
	isAIPlaying = false;
	playerPieces = 0;
	AIPieces = 0;
}

Board::~Board() {

}

int* Board::getCasePlayer() {
	return casePlayer;
}

void Board::printCases() {
	printf("Player ");
	for (int i = 0; i < sizeof(casePlayer) / sizeof(*casePlayer); i++) {
		printf("%d ", casePlayer[i]);
	}
	printf("\n");
	printf("AI ");

	for (int i = 0; i < sizeof(caseOrdi) / sizeof(*casePlayer); i++) {
		printf("%d ", caseOrdi[i]);
	}
}