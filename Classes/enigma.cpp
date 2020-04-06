#include "enigma.h"
#include <iostream>
Enigma::Enigma(const Enigma& enigmaToCopy) {
	this->firstRotated = enigmaToCopy.firstRotated;
	this->secondRotated = enigmaToCopy.secondRotated;
	this->drumCount = enigmaToCopy.drumCount;
	this->reflector = enigmaToCopy.reflector;
	this->drum = new Drum[drumCount];
	this->newDrumPtr = drum;
	for (int i = 0; i < drumCount; i++) {
		this->drum[i] = enigmaToCopy.drum[i];
		newDrumPtr++;
	}
}

Enigma::Enigma(int drumCount){
	this->firstRotated = false;
	this->secondRotated = false;
	this->drumCount = drumCount;
	this->drum = new Drum[drumCount];
	this->newDrumPtr = drum;
}

Enigma::~Enigma() {
	delete[] drum;
}

Enigma& Enigma::operator=(Enigma&& enigmaToCopy)
{
	this->firstRotated = enigmaToCopy.firstRotated;
	this->secondRotated = enigmaToCopy.secondRotated;
	this->drumCount = enigmaToCopy.drumCount;
	this->reflector = enigmaToCopy.reflector;
	this->drum = enigmaToCopy.drum;
	this->newDrumPtr = enigmaToCopy.newDrumPtr;
	enigmaToCopy.drum = new Drum;
	return *this;
}

void Enigma::addDrum(Drum drum, int position){
	newDrumPtr->moveDrum(std::move(drum));
	newDrumPtr->setPosition(position);
	newDrumPtr++;
}
void Enigma::addReflector(Reflector reflector) {
	this->reflector.moveRefl(std::move(reflector));
}

int Enigma::cipher(int in, bool firstInput){
	rotateDrums();

	int out = getCipherResult(in - 1);
	return out + 1; //shifts input to match Enigmas operable number space: (0,inf)
}

void Enigma::rotateDrums() {
	if (drumCount >= 3 && drum[1].letsNeighbourRotate() && secondRotated) {
		drum[2].rotate();
		drum[1].rotate();
	}
	else if (drumCount >= 2 && drum[0].letsNeighbourRotate() && firstRotated) {
		drum[1].rotate();
		secondRotated = true;
	}
	drum[0].rotate();
	firstRotated = true;
}


int Enigma::getCipherResult(int in) {
	int signal = in;
	for (int i = 0; i < drumCount; i++) {
		signal = drum[i].forward(signal);
	}

	signal = reflector.reverse(signal);

	for (int i = drumCount - 1; i >= 0; i--) {
		signal = drum[i].back(signal);
	}
	return signal;
}