#pragma once
#include "Component.h"
#include "Controllable.h"

class Position : public Component, public Controllable
{
public:
	void assignPointers(GameObject* parent);
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);
private:
	int* x;
	int* y;
};