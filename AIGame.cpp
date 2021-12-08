//#pragma GCC optimize("0fast")
//#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include "src/Board.h"
#include "src/IA.h"
#include <ctime>
#include <string>


void printTab(int *tab) {
    for (int i = 0; i < TAB_VALUES_SIZE; i++) {
        printf(" [%d] ", tab[i]);
    }
    printf("\n\n\n------------------------------------\n\n\n");
}


void winner(const Board &board) {
    // famine
    printf("j1 seeds %d\n", board.getNbJ1Seeds());
    printf("j2 seeds %d\n", board.getNbJ2Seeds());
    printf("J1 PIECES %d\n", board.getNbJ1Pieces());
    printf("J2 PIECES %d\n", board.getNbJ2Pieces());
    printf("SEEDS %d\n", board.getNbSeeds());
    if (board.getNbJ1Pieces() > 32) {
        printf("J1 WIN\n");
    } else if (board.getNbJ2Pieces() > 32) {
        printf("J2 WIN\n");
    } else if (board.getNbJ1Seeds() == 0) {
        printf("J2 WIN\n");
    } else if (board.getNbJ2Seeds() == 0) {
        printf("J1 WIN\n");
    } else if (board.getNbJ1Pieces() == 32 && board.getNbJ2Pieces() == 32) {
        printf("DRAW\n");
    } else if (board.getNbSeeds() < 8) {
        if (board.getNbJ2Pieces() > board.getNbJ1Pieces()) {
            printf("J2 WIN\n");
        } else if (board.getNbJ2Pieces() < board.getNbJ1Pieces()) {
            printf("J1 WIN\n");
        } else {
            printf("DRAW\n");
        }
    } else {
        printf("win ???\n");
    }
}


string inputPlayer(bool isJ1) {
    if (isJ1) {
        printf("\n\nJ1 : ");
    } else {
        printf("\n\nJ2 : ");
    }
    string s;
    getline(cin, s);
    return s;
}

pair<int, bool> parse(string s) {
    char color = s.back();
    int x;
    bool isRed;
    if (color == 'B' || color == 'b') {
        isRed = false;
    } else if (color == 'R' || color == 'r') {
        isRed = true;
    } else {
        return make_pair(-1, color);
    }

    try {
        x = stoi(s);
    } catch (const exception &ignored) {
//         ignored.what();
    }

    if (x < 1 || x > SIZE) {
        return make_pair(-1, color);
    }

    return make_pair(x - 1, isRed); // tab index from 0 to 15
}

pair<int, bool> getPlayerMove(bool isJ1) {
    string s = inputPlayer(isJ1);
    return parse(s);
}

pair<int, bool> getIAMove(Board board, bool isJ1, int depthMax, int *winNbMove) {
    int x;
    bool isRed;
    long long acc = 0;
    clock_t time_req = clock();

    if (isJ1) {
        cout << "IA J1 Turn:" << endl;
    }
    else {
        cout << "IA J2 Turn:" << endl;
    }

    depthMax = evaluateDepth(board, isJ1, depthMax);
    cout << "Depth: " << depthMax << endl;

    x = negamax(board, true, 0, depthMax, &acc, isJ1, true);

    cout << "Number of nodes: " << acc << endl;
    cout << "Time to respond: " << (float) (clock() - time_req) / CLOCKS_PER_SEC << endl;

    if (x < SIZE) {
        isRed = true;
        cout << "Move: " << x+1 << "R" << endl;
    } else {
        isRed = false;
        x -= SIZE;
        cout << "Move: " << x+1 << "B" << endl;
    }

    return make_pair(x, isRed);
}

void gameLoop(Board board) {
    int nbTour = 0;

    int winNbMoveJ1 = 20;
    int winNbMoveJ2 = 20;


    while (!board.isEnd(true, board.getIsJ1Turn())) {
        int x;
        bool isRed;
        bool validMove;

        cout << "\n\n";
        cout << "############################################################################" << endl;
        cout << "Tour: " << nbTour << endl;
        board.printCases();
        if (board.getIsJ1Turn()) {
//            pair<int, bool> res = getPlayerMove(true);
            pair<int, bool> res = getIAMove(board, true, 7, &winNbMoveJ1);
            x = res.first;
            isRed = res.second;
        }
        else {
            pair<int, bool> res = getIAMove(board, false, 2, &winNbMoveJ2);
            x = res.first;
            isRed = res.second;
        }


        if (x == -1) {
            cout << "Coup invalide !" << endl;
            continue;
        }
        validMove = board.play(x, isRed);
        if (validMove) {
            board.nextPlayer();
        }
        nbTour++;
    }
    board.printCases(); // etat final du jeu
    printf("\n");

    winner(board);
}

int main() {
    Board board = Board();
    gameLoop(board);
    return EXIT_SUCCESS;
}
