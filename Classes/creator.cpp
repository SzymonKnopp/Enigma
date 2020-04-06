#include "creator.h"
using namespace std;

Creator::Creator(){
	cin >> letterCount;
}

Drum Creator::newDrum(){
	Drum drum;

	int* cable = filledTab(letterCount);
	drum.addCables(cable, letterCount);

	int unlockPosCount;
	cin >> unlockPosCount;
	int* unlockPos = filledTab(unlockPosCount);
	drum.addUnlockPos(unlockPos, unlockPosCount);

	return drum;
}

Reflector Creator::newReflector(){
	Reflector reflector;
	int* cable = filledTab(letterCount);
	reflector.addCables(cable, letterCount);
	return reflector;
}

int* Creator::filledTab(int tabSize) {
	int* tab = new int[tabSize];
	for (int i = 0; i < tabSize; i++) {
		cin >> tab[i];
		tab[i] -= 1; //shifts input to match Enigmas operable number space: (0,inf)
	}
	return tab;
}
