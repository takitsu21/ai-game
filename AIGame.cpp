#include <iostream>
#include "Board.h"

using namespace std;


int inputPlayer(bool isJ1)
{
	if (isJ1) {
		printf("\nJ1 : ");
	} 
	else
	{
		printf("\nJ2 : ");
	}
	int x;
	cin >> x;
	return x;
}


void loop(Board board)
{

	while (!board.isEnd()) {
		board.printCases();
		int x;
		x = inputPlayer(board.getIsJ1());
		board.play(x);
		board.setNextPlayer();
	}

	if (board.getIsJ1())
	{
		printf("J2 win\n");
	}
	else
	{
		printf("J1 win\n");
	}
}


int main()
{
	Board board = Board();
	loop(board);
	return EXIT_SUCCESS;
}
