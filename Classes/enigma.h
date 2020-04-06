#pragma once
#include "drum.h"
#include "reflector.h"

class Enigma {
	//WORKS ON INTEGERS FORM 0!!!
public:
	Enigma(const Enigma& enigma);
	Enigma(int drumCount);
	~Enigma();

	Enigma& operator=(Enigma&& right);

	void addDrum(Drum drum, int position);
	void addReflector(Reflector reflector);
	int cipher(int in, bool firstInput);

private:
	Drum* drum;
	int drumCount;
	Drum* newDrumPtr;
	Reflector reflector;
	bool firstRotated;
	bool secondRotated;

	void rotateDrums();
	int getCipherResult(int in);
};
