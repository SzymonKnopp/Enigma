#pragma once
class Reflector {
public:
	~Reflector();

	void addCables(int cable[]);
	int reverse(int in);

private:
	int* cable;
};

