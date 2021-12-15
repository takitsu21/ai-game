//
// Created by Dylann on 15/12/2021.
//

#include "AllIA.h"

int AllIA::evaluate(Board board, bool isJ1, bool AIPlaying, int depth, int depthMax) {
    int x;

    int nbJ2Seeds = board.getNbJ2Seeds();
    int nbJ1Seeds = board.getNbJ1Seeds();
    int J2Pieces = board.getNbJ2Pieces();
    int J1Pieces = board.getNbJ1Pieces();
    int nbSeeds = board.getNbSeeds();
    int nbJ1RedSeeds = board.nbJ1RedSeeds;
    int nbJ2RedSeeds = board.nbJ2RedSeeds;
    int nbJ1BlueSeeds = board.nbJ1BlueSeeds;
    int nbJ2BlueSeeds = board.nbJ2BlueSeeds;

    if (isJ1) {
        if (!AIPlaying && nbJ2Seeds <= 0) { // Si on est joueur 1 et qu'on évalue un coup de l'IA
            x = 64;
        } else if (AIPlaying && nbJ1Seeds <= 0) { // on évalue le coup de l'adversaire (J2)
            return -64;
        } else if (J2Pieces > 32) {
            return -64;
        } else if (J1Pieces > 32) {
            x = 64;
        } else if (nbSeeds < 8 && J1Pieces < J2Pieces) {
            return -64;
        } else if (nbSeeds < 8 && J1Pieces > J2Pieces) {
            x = 64;
        } else {
            x = J1Pieces - J2Pieces;
        }
//        x += (nbJ1Seeds - nbJ2Seeds) / 10;
//        x += (nbJ1BlueSeeds - nbJ2BlueSeeds) / 10;
//        x += (nbJ1RedSeeds - nbJ2RedSeeds) / 10;
        if (nbJ1Seeds < nbJ2Seeds) {
            x -= 1;
        } else if (nbJ1Seeds > nbJ2Seeds) {
            x += 1;
        }
        if (nbJ1BlueSeeds > nbJ2BlueSeeds) {
            x += 1;
        } else if (nbJ2BlueSeeds > nbJ1BlueSeeds) {
            x -= 1;
        }
    } else {
        if (!AIPlaying && nbJ1Seeds <= 0) { // Si on est joueur 2 et qu'on évalue notre propre coup
            x = 64;
        } else if (AIPlaying && nbJ2Seeds <= 0) { // on évalue le coup de l'adversaire (J2)
            return -64;
        } else if (J1Pieces > 32) {
            return -64;
        } else if (J2Pieces > 32) {
            x = 64;
        } else if (nbSeeds < 8 && J2Pieces < J1Pieces) {
            return -64;
        } else if (nbSeeds < 8 && J2Pieces > J1Pieces) {
            x = 64;
        } else {
            x = J2Pieces - J1Pieces;
        }
//        x += (nbJ2Seeds - nbJ1Seeds) / 10;
//        x += (nbJ2BlueSeeds - nbJ1BlueSeeds) / 10;
//        x += (nbJ2RedSeeds - nbJ1RedSeeds) / 10;
        if (nbJ2Seeds < nbJ1Seeds) {
            x -= 1;
        } else if (nbJ2Seeds > nbJ1Seeds) {
            x += 1;
        }
        if (nbJ1BlueSeeds < nbJ2BlueSeeds) {
            x += 1;
        } else if (nbJ2BlueSeeds < nbJ1BlueSeeds) {
            x -= 1;
        }
    }
    x += depthMax - depth;
    return x;
}
