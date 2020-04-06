#include <iostream>
#include "Classes/enigma.h"
#include "Classes/creator.h"
using namespace std;

void cipherMessage(Enigma enigma);
Reflector reflPicked(Reflector* reflStored);
Drum drumPicked(Drum* drumStored);
void addDrum(Enigma* enigma, Drum* drumStored);
Enigma* constructEnigma(Drum* drumStored, Reflector* reflStored);
Reflector* newReflectors(Creator creator);
Drum* newDrums(Creator creator);

int main() {
	Creator creator;
	Drum* drumStored = newDrums(creator);
	Reflector* reflStored = newReflectors(creator);

	int taskCount;
	cin >> taskCount;
	for (int i = 0; i < taskCount; i++) {
		Enigma* enigma = constructEnigma(drumStored, reflStored);
		cipherMessage(*enigma);
	}

	delete[] drumStored;
	delete[] reflStored;
	return 0;
}

Drum* newDrums(Creator creator) {
	int drumCount;
	cin >> drumCount;
	Drum* drum = new Drum[drumCount];

	for (int i = 0; i < drumCount; i++) {
		drum[i].moveDrum(move(creator.newDrum()));
	}
	return drum;
}
Reflector* newReflectors(Creator creator) {
	int reflCount;
	cin >> reflCount;
	Reflector* reflector = new Reflector[reflCount];

	for (int i = 0; i < reflCount; i++) {
		reflector[i].moveRefl(move(creator.newReflector()));
	}
	return reflector;
}

Enigma* constructEnigma(Drum* drumStored, Reflector* reflStored) {
	int drumCount;
	cin >> drumCount;
	Enigma* enigma = new Enigma(drumCount);

	for (int i = 0; i < drumCount; i++) {
		addDrum(enigma, drumStored);
	}

	enigma->addReflector(reflPicked(reflStored));

	return enigma;
}
void addDrum(Enigma* enigma, Drum* drumStored) {
	Drum drum = drumPicked(drumStored);
	int position;
	cin >> position;
	enigma->addDrum(drum, position);
}
//drumPicked and reflPicked can be merged to one compPicked,
//if Component class would be created and inheriting applied
Drum drumPicked(Drum* drumStored) {
	int drumPicked;
	cin >> drumPicked;
	return drumStored[drumPicked];
}
Reflector reflPicked(Reflector* reflStored) {
	int reflPicked;
	cin >> reflPicked;
	return reflStored[reflPicked];
}

void cipherMessage(Enigma enigma) {
	int in;
	cin >> in;
	cout << enigma.cipher(in, true) << ' ';

	while (true) {
		int input;
		cin >> input;
		if (input == 0)
			break;
		cout << enigma.cipher(input, false) << ' ';
	}
	cout << endl;
}