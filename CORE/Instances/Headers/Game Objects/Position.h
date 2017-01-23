#pragma once
#include "Component.h"
#include "Controllable.h"
#include "Definer.h"

class Position : public Component
{
public:
	Position();
	Position(Definer* definer);
	Position(Position&);
	virtual Component* spawnCopy();
	virtual void move(int aX, int aY);
	void assignPointers(Entity* parent);

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);
protected:
	SimpleData<int>* x;
	SimpleData<int>* y;
};