#include "Board.h"


Board::Board() {
    for (int i = 0; i < SIZE; i++) {
        redCase[i] = 2;
        blueCase[i] = 2;
        isJ1Case[i] = i % 2 == 0;
    }
    nbJ1Seeds = 32;
    nbJ2Seeds = 32;
    nbSeeds = MAX_SEEDS;
    isJ1Turn = true;
    J2Pieces = 0;
    J1Pieces = 0;
}

Board::Board(bool test) {}

Board::Board(const Board &obj) {
    for (int i = 0; i < SIZE; i++) {
        redCase[i] = obj.redCase[i];
        blueCase[i] = obj.blueCase[i];
        isJ1Case[i] = obj.isJ1Case[i];
    }
    nbJ1Seeds = obj.nbJ1Seeds;
    nbJ2Seeds = obj.nbJ2Seeds;
    nbSeeds = obj.nbSeeds;
    isJ1Turn = obj.isJ1Turn;
    J2Pieces = obj.J2Pieces;
    J1Pieces = obj.J1Pieces;
}

Board Board::copy() {
    Board b = Board(true);
    for (int i = 0; i < SIZE; i++) {
        b.redCase[i] = redCase[i];
        b.blueCase[i] = blueCase[i];
        b.isJ1Case[i] = isJ1Case[i];
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

void Board::printCases() {
    printf("score J1 : %d\nscore J2 : %d\n\n", J1Pieces, J2Pieces);

    for (int i = 0; i < SIZE / 2; i++) {
        printf("|%dR %dB| ",
               redCase[i], blueCase[i]);
    }
    printf("\n");
    for (int i = 1; i <= SIZE / 2; i++) {
        printf("   %d    ", i);
    }
    printf("\n---------------------------------------------------------------\n");

    for (int i = SIZE - 1; i >= SIZE / 2; i--) {
        printf("|%dR %dB| ",
               redCase[i], blueCase[i]);
    }

    printf("\n");
    for (int i = SIZE; i > SIZE / 2; i--) {
        printf("   %d   ", i);
    }
    std::cout << "\n\n";
}


bool Board::getIsJ1Turn() const {
    return isJ1Turn;
}


bool Board::play(int move, bool isRed) {
    int seeds;

    if (!checkValidMove(move, isRed)) {
        printf("Coup invalide !\n");
        return false;
    }
    if (isRed) {
        seeds = redCase[move];
        redCase[move] = 0;
    } else {
        seeds = blueCase[move];
        blueCase[move] = 0;
    }

    int index = move;

    bool start = true;
    while (seeds > 0) {

        if (isRed) { // sur toutes les cases
            if (start) {
                start = false;
                index++;
            }
            if (index == move) {
                index++;
            }
            if (index >= SIZE) {
                index = 0;
            }
            // joue
            redCase[index]++;
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
            blueCase[index]++;
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
    nbJ1Seeds = 0;
    nbJ2Seeds = 0;
    for (int i = 0; i < SIZE; i++) {
        if (isJ1Case[i]) {
            nbJ1Seeds += blueCase[i] + redCase[i];
        } else {
            nbJ2Seeds += blueCase[i] + redCase[i];
        }
    }
    return true;
}


bool Board::isEnd() const {
    return ((J1Pieces > 32 || J2Pieces > 32)
            || (nbJ1Seeds == 0 || nbJ2Seeds == 0)
            || (J1Pieces == 32 && J2Pieces == 32)
            || (nbSeeds < 8));
}


bool Board::checkValidMove(int move, bool isRed) {
    if (move >= 0 && move <= SIZE - 1) { // si le coup est bon
        if ((isRed && redCase[move] > 0)
            || (!isRed && blueCase[move] > 0)) { // si le pot de couleur selectionner n'est pas vide

            if ((isJ1Turn && isJ1Case[move])
                || (!isJ1Turn && !isJ1Case[move])) { // si j1 turn et il joue danssa case alors oui, idem j2
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
        int total = redCase[index] + blueCase[index];
        if (total == 3 || total == 2) {
            gain += total;
            blueCase[index] = 0;
            redCase[index] = 0;
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


int Board::evaluate(bool isJ1, bool AIPlaying) const {

    int x;

    if (isJ1) {
        if (!AIPlaying && nbJ2Seeds <= 0) { // Si on est joueur 1 et qu'on évalue un coup de l'IA
            x = 64;
        }
        else if (AIPlaying && nbJ1Seeds <= 0) { // on évalue le coup de l'adversaire (J2)
            x = -64;
        }
        else if (J2Pieces > 32) {
            x = -64;
        } else if (J1Pieces > 32) {
            x = 64;
        } else if (nbSeeds < 8 && J1Pieces < J2Pieces ) {
            x = -64;
        } else if ( nbSeeds < 8 && J1Pieces > J2Pieces) {
            x = 64;
        } else {
            x = J1Pieces - J2Pieces;
        }
    }
    else {
        if (!AIPlaying && nbJ1Seeds <= 0) { // Si on est joueur 2 et qu'on évalue notre propre coup
            x = 64;
        }
        else if (AIPlaying && nbJ2Seeds <= 0) { // on évalue le coup de l'adversaire (J2)
            x = -64;
        }
        else if (J1Pieces > 32) {
            x = -64;
        } else if (J2Pieces > 32) {
            x = 64;
        } else if (nbSeeds < 8 && J2Pieces < J1Pieces) {
            x = -64;
        } else if (nbSeeds < 8 && J2Pieces > J1Pieces) {
            x = 64;
        } else {
            x = J2Pieces - J1Pieces;
        }
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

int Board::getNbSeeds() const {
    return nbSeeds;
}