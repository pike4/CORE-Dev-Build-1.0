#pragma once
#include "Component.h"
#include "Controllable.h"
#include "Node.h"

class Position : public Component
{
public:
	Position();
	Position(Node* definer); // must go
	Position(Position&);

	virtual void getText(Node* def);
	virtual void get_data(DataSource* source);

	virtual Component* spawnCopy();
	virtual void move(int aX, int aY);

	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0);
protected:
	DataImpl<int>* x;
	DataImpl<int>* y;
};