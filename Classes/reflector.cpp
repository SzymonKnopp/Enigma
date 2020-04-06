#include "reflector.h"

Reflector::Reflector() {
	this->letterCount = 0;
	this->cable = nullptr;
}
Reflector::Reflector(const Reflector& reflToCopy) {
	this->letterCount = reflToCopy.letterCount;
	this->cable = allocateAndCopyCables(reflToCopy.cable, letterCount);
}

Reflector::~Reflector() {
	delete[] cable;
}

void Reflector::moveRefl(Reflector&& reflToCopy)
{
	this->letterCount = reflToCopy.letterCount;
	this->cable = reflToCopy.cable;
	reflToCopy.cable = nullptr;
}

void Reflector::addCables(int cable[], int letterCount) {
	this->letterCount = letterCount;
	this->cable = allocateAndCopyCables(cable, letterCount);
}

int Reflector::reverse(int in) {
	return cable[in];
}

int* Reflector::allocateAndCopyCables(int* cablesToCopy, int count) {
	int* newCable = new int[count];
	for (int i = 0; i < count; i++) {
		newCable[i] = cablesToCopy[i];
	}
	return newCable;
}