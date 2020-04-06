#include <iostream>
#include "enigmaParts.h"

using namespace std;

void deleteRotor(rotor rot);
void rotateRotors(bool didRotate[], rotor* rotors, int rotorAmount);
void codeMessage(rotor* rotors, int rotorAmount, reflector reflector);
void processCode(rotor* rotorsSaved, reflector* reflectorsSaved);
reflector getReflector(int alphabetSize);
reflector* getReflectors(int alphabetSize, int amount);
void setInAndOut(int alphabetSize, rotor* newRotor);
void setNotches(rotor* newRotor, int notchAmount);
rotor getRotor(int alphabetSize);
rotor* getRotors(int alphabetSize, int amount);
reflector addReflector(reflector* reflectorsSaved);
rotor addRotor(rotor* rotorsSaved);


int main() {
	int alphabetSize;
	cin >> alphabetSize;
	
	int rotorAmount;
	cin >> rotorAmount;
	rotor* rotorsSaved = getRotors(alphabetSize, rotorAmount);

	int reflectorAmount;
	cin >> reflectorAmount;
	reflector* reflectorsSaved = getReflectors(alphabetSize, reflectorAmount);

	int codeAmount;
	cin >> codeAmount;
	for (int i = 0; i < codeAmount; i++) {
		processCode(rotorsSaved, reflectorsSaved);
	}

	//DEBUG
	/*
	cout << "Rotors:" << endl;
	for (int i = 0; i < rotorAmount; i++) {
		rotor rot = rotorsSaved[i];
		for (int j = 0; j < alphabetSize; j++) {
			cout << rot.in[j];
		}
		cout << " notches: ";
		for (int j = 0; j < rot.notchAmount; j++) {
			cout << rot.notches[j];
		}
		cout << endl;
	}
	cout << "Reflectors:" << endl;
	for (int i = 0; i < reflectorAmount; i++) {
		for (int j = 0; j < alphabetSize; j++) {
			cout << reflectorsSaved[i].in[j];
		}
		cout << endl;
	}
	rotor copy = copyRotor(rotorsSaved[0]);
	cout << "Copy of first rotor: " << endl;
	for (int j = 0; j < alphabetSize; j++) {
		cout << copy.in[j];
	}
	cout << " notches: ";
	for (int j = 0; j < copy.notchAmount; j++) {
		cout << copy.notches[j];
	}
	cout << endl;
	setPosition(&copy, 4);
	cout << "Copy position: " << copy.pos << endl;
	rotate(&copy);
	cout << "Copy position: " << copy.pos << endl;
	rotate(&copy);
	cout << "Copy position: " << copy.pos << endl << endl;
	//ROTORS AND REFLECTORS WORK ON NUMBERS (0,inf)
	//SHIFT INPUT BY -1 BEFORE CODING
	int signal = 2;
	signal--;
	cout << "Coding of '2' inwards by copy: " << signal << " -> " << codeIn(copy,signal) << " (unshifted: " << codeIn(copy, signal) + 1 << ")" << endl;
	cout << "Coding of '2' outwards by copy: " << signal << " -> " << codeOut(copy, signal) << " (unshifted: " << codeOut(copy, signal) + 1 << ")" << endl;
	cout << "Coding of '2' by reflector[0]: " << signal << " -> " << reflectorsSaved[0].in[signal] << " (unshifted: " << reflectorsSaved[0].in[signal] + 1 << ")" << endl << endl;

	cout << "Is rotor 'copy' on position " << copy.pos + 1;
	cout << " allowing next rotor to turn? " << onNotch(copy) << endl;

	deleteRotor(copy);
	cout << "Rotors after deletion of copy:" << endl;
	for (int i = 0; i < rotorAmount; i++) {
		rotor rot = rotorsSaved[i];
		for (int j = 0; j < alphabetSize; j++) {
			cout << rot.in[j];
		}
		cout << " notches: ";
		for (int j = 0; j < rot.notchAmount; j++) {
			cout << rot.notches[j];
		}
		cout << endl;
	}
	*/
	//DEBUG END
	for (int i = 0; i < rotorAmount; i++) {
		deleteRotor(rotorsSaved[i]);
	}
	delete[] rotorsSaved;

	for (int i = 0; i < reflectorAmount; i++) {
		delete reflectorsSaved[i].in;
	}
	delete[] reflectorsSaved;

	return 0;
}

rotor* getRotors(int alphabetSize, int amount) {
	rotor* rotors = new rotor[amount];

	for (int i = 0; i < amount; i++) {
		rotors[i] = getRotor(alphabetSize);
	}

	return rotors;
}
rotor getRotor(int alphabetSize) {
	rotor newRotor;
	newRotor.posAmount = alphabetSize;
	setInAndOut(alphabetSize, &newRotor);

	int notchAmount;
	cin >> notchAmount;
	newRotor.notchAmount = notchAmount;
	setNotches(&newRotor, notchAmount);

	return newRotor;
}
void setInAndOut(int alphabetSize, rotor* newRotor) {
	newRotor->in = new int[alphabetSize];
	newRotor->out = new int[alphabetSize];
	for (int i = 0; i < alphabetSize; i++) {
		int letter;
		cin >> letter;
		letter--;
		newRotor->in[i] = letter;
		newRotor->out[letter] = i;
	}
}
void setNotches(rotor* newRotor, int notchAmount) {
	newRotor->notches = new int[notchAmount];
	for (int i = 0; i < notchAmount; i++) {
		cin >> newRotor->notches[i];
		newRotor->notches[i]--;
	}
}

reflector* getReflectors(int alphabetSize, int amount) {
	reflector* reflectors = new reflector[amount];
	for (int i = 0; i < amount; i++) {
		reflectors[i] = getReflector(alphabetSize);
	}
	return reflectors;
}
reflector getReflector(int alphabetSize) {
	reflector newReflector;
	newReflector.in = new int[alphabetSize];
	for (int i = 0; i < alphabetSize; i++) {
		cin >> newReflector.in[i];
		newReflector.in[i]--;
	}
	return newReflector;
}

void processCode(rotor* rotorsSaved, reflector* reflectorsSaved) {
	int rotorAmount;
	cin >> rotorAmount;
	rotor* rotorsIn = new rotor[rotorAmount];
	for (int i = 0; i < rotorAmount; i++) {
		rotorsIn[i] = addRotor(rotorsSaved);
	}

	reflector reflectorIn = addReflector(reflectorsSaved);

	codeMessage(rotorsIn, rotorAmount, reflectorIn);

	for (int i = 0; i < rotorAmount; i++) {
		deleteRotor(rotorsIn[i]);
	}
}
rotor addRotor(rotor* rotorsSaved) {
	rotor newRotor;
	int rotorPicked;
	cin >> rotorPicked;
	newRotor = copyRotor(rotorsSaved[rotorPicked]);

	int positionPicked;
	cin >> positionPicked;
	setPosition(&newRotor, positionPicked);

	return newRotor;
}
reflector addReflector(reflector* reflectorsSaved) {
	int reflectorPicked;
	cin >> reflectorPicked;
	return reflectorsSaved[reflectorPicked];
}

void codeMessage(rotor* rotors, int rotorAmount, reflector reflector) {
	bool didRotate[2] = { false,false };
	while (true) {
		int letter;
		cin >> letter;
		if (letter == 0)
			break;
		letter--;

		rotateRotors(didRotate, rotors, rotorAmount);

		for (int i = 0; i < rotorAmount; i++) {
			letter = codeIn(rotors[i], letter);
		}
		letter = reflector.in[letter];
		for (int i = rotorAmount - 1; i >= 0; i--) {
			letter = codeOut(rotors[i], letter);
		}
		cout << letter + 1 << " ";
	}
	cout << endl;
}
void rotateRotors(bool didRotate[], rotor* rotors, int rotorAmount) {
	if (rotorAmount >= 3 && didRotate[1] && onNotch(rotors[1])) {
		rotate(&(rotors[2]));
		rotate(&(rotors[1]));
	}
	else if (rotorAmount >= 2 && didRotate[0] && onNotch(rotors[0])) {
		rotate(&(rotors[1]));
		didRotate[1] = true;
	}
	rotate(&(rotors[0]));
	didRotate[0] = true;
}

void deleteRotor(rotor rot) {
	delete[] rot.in;
	delete[] rot.out;
	delete[] rot.notches;
}