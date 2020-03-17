#pragma once
class Drum {
public:
	Drum();
	~Drum();

	void addCables(int cable[], int letterCount);
	void addUnlockPos(int unlockPos[], int unlockPosCount);
	int forward(int in);
	int back(int in);
	bool letsNeighbourRotate();
	bool matchedWithFuturePos(int testValue);
	void rotate();
	void setPosition(int position);

private:
	int* forwardCable;
	int* backCable;
	int position;
	int* unlockPos;
	int unlockPosCount;
	int letterCount;

	int adjustToPos(int in);
	int unAdjust(int in);
};

