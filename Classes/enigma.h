#pragma once
#include "drum.h"
#include "reflector.h"

class Enigma {
	//WORKS ON INTEGERS FORM 0!!!
public:
	Enigma(int drumCount);
	~Enigma();

	void addDrum(Drum drum, int position);
	void addReflector(Reflector reflector);
	int cipher(int in, bool firstInput);

private:
	Drum* drum;
	int drumCount;
	Drum* newDrumPtr;
	Reflector reflector;

	void rotateDrums();
	int getCipherResult(int in);
};
