#include "Board.h"

bool isEmpty(Case *boardCase) {
    for (int i = 0; i < SIZE; i++) {
        if (boardCase[i].getTotal() != 0) {
            return false;
        }
    }
    return true;
}

Board::Board() {
    for (int i = 0; i < SIZE; i++) {
        boardCase[i].setNbRed(2);
        boardCase[i].setNbBlue(2);
        boardCase[i].setIsJ1(i % 2 == 0);
    }
    nbJ1Seeds = 32;
    nbJ2Seeds = 32;
    nbSeeds = MAX_SEEDS;
    isJ1Turn = true;
    J2Pieces = 0;
    J1Pieces = 0;
}

Board::Board(bool test) {}


Board Board::copy() {
    Board b = Board(true);
    for (int i = 0; i < SIZE; i++) {
        b.boardCase[i] = boardCase[i];
    }
    b.nbJ1Seeds = nbJ1Seeds;
    b.nbJ2Seeds = nbJ2Seeds;
    b.nbSeeds = nbSeeds;
    b.isJ1Turn = isJ1Turn;
    b.J2Pieces = J2Pieces;
    b.J1Pieces = J1Pieces;

    return b;
}

Board::~Board() {

}


Case *Board::getBoardCase() {
    return boardCase;
}

void Board::printCases() {
    printf("\n\n Nouveau tour: \n");

    printf("pieces J1 : %d, pieces J2 : %d\n\n", J1Pieces, J2Pieces);

    for (int i = 0; i < SIZE / 2; i++) {
        printf("|%dR %dB| ",
               boardCase[i].getNbRed(), boardCase[i].getNbBlue());
    }
    printf("\n");
    for (int i = 1; i <= SIZE / 2; i++) {
        printf("   %d    ", i);
    }
    printf("\n---------------------------------------------------------------\n");

    for (int i = SIZE - 1; i >= SIZE / 2; i--) {
        printf("|%dR %dB| ",
               boardCase[i].getNbRed(), boardCase[i].getNbBlue());
    }

    printf("\n");
    for (int i = SIZE; i > SIZE / 2; i--) {
        printf("   %d   ", i);
    }
}


bool Board::getIsJ1Turn() {
    return isJ1Turn;
}


bool Board::play(int move, bool isRed) {
    int seeds;

    if (!checkValidMove(move, isRed)) {
        printf("Coup invalide !\n");
        return false;
    }
    if (isRed) {
        seeds = boardCase[move].getNbRed();
        boardCase[move].setNbRed(0);
    } else {
        seeds = boardCase[move].getNbBlue();
        boardCase[move].setNbBlue(0);
    }

    int index = move;

    bool start = true;
    while (seeds > 0) {

        if (isRed) { // sur toutes les cases
            if (index == move) {
                index++;
            }
            if (start) {
                start = false;
                index++;
            }
            if (index >= SIZE) {
                index = 0;
            }
            // joue
            boardCase[index].addRed();
            // incrémente
            index++;
        } else { // uniquement sur les cases de l'opposant
            if (start) {
                start = false;
                index++;
            }
            if (index >= SIZE && isJ1Turn) {
                index = 1;
            } else if (index >= SIZE) {
                index = 0;
            }
            // joue
            boardCase[index].addBlue();
            // incrémente
            index += 2;
        }
        seeds--;
    }

    if (isRed) {
        index--;
    } else {
        index -= 2;
    }

    eatSeeds(index);
    for (Case c: boardCase) {
        if (c.getIsJ1()) {
            nbJ1Seeds = c.getNbBlue() + c.getNbRed();
        } else {
            nbJ2Seeds = c.getNbBlue() + c.getNbRed();
        }
    }
    return true;
}


bool Board::isEnd() const {
//    printf("%d\n", nbSeeds);
//    printf("%d\n", J1Pieces);
//    printf("%d\n", J2Pieces);
//    printf("%d\n", nbJ1Seeds);
//    printf("%d\n", nbJ2Seeds);
    return ((J1Pieces > 32 || J2Pieces > 32)
            || (nbJ1Seeds == 0 || nbJ2Seeds == 0)
            || (J1Pieces == 32 && J2Pieces == 32)
            || (nbSeeds < 8));
}


bool Board::checkValidMove(int move, bool isRed) {
    if (move >= 0 && move <= SIZE - 1) { // si le coup est bon
        if ((isRed && boardCase[move].getNbRed() > 0)
            || (!isRed && boardCase[move].getNbBlue() > 0)) { // si le pot de couleur selectionner n'est pas vide

            if ((isJ1Turn && boardCase[move].getIsJ1())
                || (!isJ1Turn && !boardCase[move].getIsJ1())) { // si j1 turn et il joue danssa case alors oui, idem j2
                return true;
            }
        }
    }
    return false;
}


void Board::eatSeeds(int index) {
    int gain = 0;
    bool cond = true;
    while (cond) {
        if (index < 0) {
            index = SIZE - 1;
        }
        int total = boardCase[index].getTotal();
        if (total == 3 || total == 2) {
            gain += total;
            boardCase[index].setNbBlue(0);
            boardCase[index].setNbRed(0);
        } else {
            cond = false;
        }
        index--;
    }
    if (gain) {
        addPieces(gain);
    }
}


void Board::addPieces(int pieces) {
    if (isJ1Turn) {
        J1Pieces += pieces;
    } else {
        J2Pieces += pieces;
    }
    nbSeeds -= pieces;
}


int Board::evaluate(bool AIPlaying) const {
    int x = 0;
    if (AIPlaying && isJ1Turn || !AIPlaying && isJ1Turn) {
        x = J1Pieces - J2Pieces;
    }
    else if (AIPlaying && !isJ1Turn || !AIPlaying && !isJ1Turn) {
        x= J2Pieces - J1Pieces;
    }

    return x;
}

void Board::nextPlayer() {
    isJ1Turn = !isJ1Turn;
}

int Board::getNbJ1Seeds() const {
    return nbJ1Seeds;
}

int Board::getNbJ2Seeds() const {
    return nbJ2Seeds;
}

int Board::getNbJ1Pieces() const {
    return J1Pieces;
}

int Board::getNbJ2Pieces() const {
    return J2Pieces;
}
