#include "Board.h"

int Board::minMax(Board currentBoard, int depth, int depthMax)
{
    return 0;
}

Board::Board()
{
    for (int i = 0; i < SIZE; i++) {
        caseJ1[i] = 4;
        caseJ2[i] = 4;
    }
    isJ1 = true;
    J2Pieces = 0;
    J1Pieces = 0;
}

Board::~Board()
{

}

int* Board::getCaseJ2()
{
    return caseJ2;
}

int* Board::getCaseJ1()
{
    return caseJ1;
}

void Board::printCases()
{
    printf("\n Nouveau tour: \n");
    printf("J1 ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("[%d] ", caseJ1[i]);
    }
    printf("\nNp ");
    for (int i = 0; i < SIZE; i++)
    {
        printf(" %d  ", i);
    }

    printf("\n\n");
    printf("J2 ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("[%d] ", caseJ2[i]);
    }
    printf("\nNp ");
    for (int i = 0; i < SIZE; i++)
    {
        printf(" %d  ", i);
    }
}


bool Board::getIsJ1()
{
    return isJ1;
}


void Board::setIsJ1(bool isPlaying)
{
    isJ1 = isPlaying;
}


void Board::play(int coup) {
    int seeds;
    int* currentCase;
    bool isCaseJ1;

    if (isJ1)
    {
        seeds = caseJ1[coup];
        currentCase = getCaseJ1();
        isCaseJ1 = true;
    }
    else
    {
        seeds = caseJ2[coup];
        currentCase = getCaseJ2();
        isCaseJ1 = false;
    }

    int index = coup;
    int desc = false;
    currentCase[coup] = 0;

    while (seeds > 0)
    {

        if (desc)
        {
            if (index <= 0)
            {
                // index de change pas
                desc = false;
                currentCase = switchPlayer(&isCaseJ1);
                currentCase[index]++;
            }
            else
            {
                index--;
                currentCase[index]++;
            }
        }
        else
        {
            if (index >= SIZE - 1)
            {
                // index de change pas
                desc = true;
                currentCase = switchPlayer(&isCaseJ1);
                currentCase[index]++;
            }
            else
            {
                index++;
                currentCase[index]++;
            }
        }
        printf("index : %d %d %p\n", index, isCaseJ1, &currentCase);
        seeds--;
    }
    eatSeeds(index, currentCase, isCaseJ1);
    return true;
}


int* Board::switchPlayer(bool* isCaseJ1) {

    if (*isCaseJ1) {
        printf("switch to j2");
        *isCaseJ1 = !(*isCaseJ1);
        return getCaseJ2();
    }
    else {
        printf("switch else\n");
        *isCaseJ1 = !(*isCaseJ1);
        return getCaseJ1();
    }
}


bool Board::isEnd()
{
    if (isJ1) {
        return J1Pieces >= 25;
    }
    return J2Pieces >= 25;
}

void Board::setNextPlayer()
{
    isJ1 = !isJ1;
}

bool Board::checkValidMove(const int *currentCase, int move) {
    return currentCase[move] > 0 && move >= 0 && move <= 5;
}

void Board::eatSeeds(int index, int *currentCase, bool isCaseJ1) {
    if (getIsJ1() == isCaseJ1) {
        return;
    }
    while (index >= 0) {
        if (currentCase[index] == 2 || currentCase[index] == 3) {
            addPieces(currentCase[index]);
            currentCase[index] = 0;
        } else {
            break;
        }
        index--;
    }
}

void Board::addPieces(int pieces) {
    if (isJ1) {
        J1Pieces += pieces;
    } else {
        J2Pieces += pieces;
    }
}