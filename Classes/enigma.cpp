#include "enigma.h"

Enigma::Enigma(int drumCount){
	this->drumCount = drumCount;
	this->drum = new Drum[drumCount];
	this->newDrumPtr = drum;
}

Enigma::~Enigma() {
	//delete[] drum;
}

void Enigma::addDrum(Drum drum, int position){
	*newDrumPtr = drum;
	newDrumPtr->setPosition(position);
	newDrumPtr++;
}
void Enigma::addReflector(Reflector reflector) {
	this->reflector = reflector;
}

int Enigma::cipher(int in, bool firstInput){
	if (firstInput)
		drum[0].rotate();
	else 
		rotateDrums();

	int out = getCipherResult(in - 1);
	return out + 1; //shifts input to match Enigmas operable number space: (0,inf)
}

void Enigma::rotateDrums() {
	bool inRotation = false;
	for (int i = drumCount - 1; i >= 1; i--) {
		if (!inRotation && drum[i - 1].letsNeighbourRotate())
			inRotation = true;

		if (inRotation)
			drum[i].rotate();
	}
	drum[0].rotate();
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