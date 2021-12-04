//
// Created by Dylann on 04/12/2021.
//
#include "Case.h"

Case::Case() {

}

Case::~Case() {

}

bool Case::getIsJ1() {
    return isJ1;
}

int Case::getNbRed() {
    return nbRed;
}

void Case::setNbRed(int red) {
    this->nbRed = red;
}

int Case::getNbBlue() {
    return nbBlue;
}

void Case::setNbBlue(int blue) {
    this->nbBlue = blue;
}

int Case::getTotal() {
    return nbBlue + nbRed;
}


void Case::setIsJ1(bool isJ1) {
    this->isJ1 = isJ1;
}


void Case::addRed() {
    nbRed++;
}

void Case::addBlue() {
    nbBlue++;
}




