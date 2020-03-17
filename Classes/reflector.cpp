#include "reflector.h"

Reflector::~Reflector() {
	//delete[] cable;
}

void Reflector::addCables(int cable[]) {
	this->cable = cable;
}

int Reflector::reverse(int in) {
	return cable[in];
}