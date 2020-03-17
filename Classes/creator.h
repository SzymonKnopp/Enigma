#pragma once
#include <iostream>
#include "drum.h"
#include "reflector.h"

class Creator
{
public:
	Creator();
	Drum newDrum();
	Reflector newReflector();

private:
	int letterCount;

	int* filledTab(int tabSize);
};

