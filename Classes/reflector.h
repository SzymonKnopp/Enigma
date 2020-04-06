#pragma once
class Reflector {
public:
	Reflector();
	Reflector(const Reflector& reflToCopy);
	~Reflector();

	void moveRefl(Reflector&&);
	void addCables(int cable[], int letterCount);
	int reverse(int in);

	int* allocateAndCopyCables(int* cablesToCopy, int count);

private:
	int letterCount;
	int* cable;
};

