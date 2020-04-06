//REFLECTOR
struct reflector {
	int* in = nullptr;
};


//ROTOR
struct rotor {
	int* in = nullptr;
	int* out = nullptr;
	int pos = 0;
	int posAmount = 0;
	int* notches = nullptr;
	int notchAmount = 0;
};

int shiftToRotation(rotor rot, int signal);
int unshiftToRotation(rotor rot, int signal);
int* copyTab(int* old, int size);

//Functions used in main
int codeIn(rotor rot, int signal) {
	signal = shiftToRotation(rot, signal);
	signal = rot.in[signal];
	signal = unshiftToRotation(rot, signal);
	return signal;
}
int codeOut(rotor rot, int signal) {
	signal = shiftToRotation(rot, signal);
	signal = rot.out[signal];
	signal = unshiftToRotation(rot, signal);
	return signal;
}


void setPosition(rotor* rot, int position) {
	rot->pos = position - 1;
}
void rotate(rotor* rot) {
	rot->pos = (rot->pos + 1) % rot->posAmount;
}

bool onNotch(rotor rot) {
	int nextPos = (rot.pos + 1) % rot.posAmount;
	for (int i = 0; i < rot.notchAmount; i++) {
		if (rot.notches[i] == nextPos)
			return true;
	}
	return false;
}

rotor copyRotor(rotor old) {
	rotor copy;
	copy.notchAmount = old.notchAmount;
	copy.posAmount = old.posAmount;
	copy.in = copyTab(old.in, old.posAmount);
	copy.out = copyTab(old.out, old.posAmount);
	copy.notches = copyTab(old.notches, old.notchAmount);
	return copy;
}


//Functions not used in main
int shiftToRotation(rotor rot, int signal) {
	signal += rot.pos;
	signal = signal % rot.posAmount;
	return signal;
}
int unshiftToRotation(rotor rot, int signal) {
	signal -= rot.pos;
	if (signal < 0) //modulo for negative numbers
		signal += rot.posAmount;
	return signal;
}

int* copyTab(int* old, int size) {
	int* copy = new int[size];
	for (int i = 0; i < size; i++) {
		copy[i] = old[i];
	}
	return copy;
}