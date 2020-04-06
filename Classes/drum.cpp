#include "drum.h"

Drum::Drum() {
	this->position = 0;
	this->letterCount = 0;
	this->forwardCable = nullptr;
	this->backCable = nullptr;
	this->unlockPos = nullptr;
	this->unlockPosCount = 0;
}
Drum::Drum(const Drum& drumToCopy) {
	this->position = drumToCopy.position;
	this->letterCount = drumToCopy.letterCount;
	this->forwardCable = allocateAndCopyCables(drumToCopy.forwardCable, letterCount);
	this->backCable = allocateAndCopyCables(drumToCopy.backCable, letterCount);
	this->unlockPosCount = drumToCopy.unlockPosCount;
	this->unlockPos = allocateAndCopyCables(drumToCopy.unlockPos, unlockPosCount);
}

Drum::~Drum() {
	delete[] forwardCable;
	delete[] backCable;
	delete[] unlockPos;
}

void Drum::moveDrum(Drum&& drumToMove)
{
	this->position = drumToMove.position;
	this->letterCount = drumToMove.letterCount;
	this->forwardCable = drumToMove.forwardCable;
	drumToMove.forwardCable = nullptr;
	this->backCable = drumToMove.backCable;
	drumToMove.backCable = nullptr;
	this->unlockPosCount = drumToMove.unlockPosCount;
	this->unlockPos = drumToMove.unlockPos;
	drumToMove.unlockPos = nullptr;
}

/*
Drum& Drum::operator=(Drum&& drumToCopy)
{
	this->position = drumToCopy.position;
	this->letterCount = drumToCopy.letterCount;
	this->forwardCable = drumToCopy.forwardCable;
	drumToCopy.forwardCable = nullptr;
	this->backCable = drumToCopy.backCable;
	drumToCopy.backCable = nullptr;
	this->unlockPosCount = drumToCopy.unlockPosCount;
	this->unlockPos = drumToCopy.unlockPos;
	drumToCopy.unlockPos = nullptr;
	return *this;
}
*/

void Drum::addCables(int cable[], int letterCount) {
	this->letterCount = letterCount;
	this->forwardCable = allocateAndCopyCables(cable, letterCount);

	this->backCable = new int[letterCount];
	for (int out = 0; out < letterCount; out++) {
		int in = cable[out];
		backCable[in] = out;
	}
}
void Drum::addUnlockPos(int unlockPos[], int unlockPosCount) {
	this->unlockPosCount = unlockPosCount;
	this->unlockPos = allocateAndCopyCables(unlockPos, unlockPosCount);
}

int Drum::forward(int in) {
	in = adjustToPos(in);
	int out = forwardCable[in];
	out = unAdjust(out);
	return out;
}
int Drum::back(int in) {
	in = adjustToPos(in);
	int out = backCable[in];
	out = unAdjust(out);
	return out;
}
int Drum::adjustToPos(int in) {
	return (in + position) % letterCount;
}
int Drum::unAdjust(int in) {
	int out = (in - position) % letterCount;
	//Modulo in negative numbers
	if (out < 0)
		return out + letterCount;
	else return out;
}

bool Drum::letsNeighbourRotate() {
	for (int i = 0; i < unlockPosCount; i++) {
		if (matchedWithFuturePos(unlockPos[i]))
			return true;
	}
	return false;
}
bool Drum::matchedWithFuturePos(int testValue) {
	int futurePos = (position + 1) % letterCount;
	if (testValue == futurePos)
		return true;
	else return false;
}

void Drum::setPosition(int position) {
	this->position = position - 1; //shifts input to match Enigmas operable number space: (0,inf)
}
void Drum::rotate() {
	position = (position + 1) % letterCount;
}

int* Drum::allocateAndCopyCables(int* cablesToCopy, int count) {
	int* newCable = new int[count];
	for (int i = 0; i < count; i++) {
		newCable[i] = cablesToCopy[i];
	}
	return newCable;
}