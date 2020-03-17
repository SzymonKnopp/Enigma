#include "drum.h"

Drum::Drum() {
	this->position = 0;
	this->letterCount = 0;
	this->forwardCable = nullptr;
	this->backCable = nullptr;
	this->unlockPos = nullptr;
	this->unlockPosCount = 0;
}
Drum::~Drum() {
	//delete[] forwardCable;
	//delete[] backCable;
	//delete[] unlockPos;
}

void Drum::addCables(int cable[], int letterCount) {
	this->letterCount = letterCount;
	this->forwardCable = cable;

	this->backCable = new int[letterCount];
	for (int out = 0; out < letterCount; out++) {
		int in = cable[out];
		backCable[in] = out;
	}
}
void Drum::addUnlockPos(int unlockPos[], int unlockPosCount) {
	this->unlockPos = unlockPos;
	this->unlockPosCount = unlockPosCount;
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