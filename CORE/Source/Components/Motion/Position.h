#pragma once
#include "Component.h"
#include "Controllable.h"
#include "DefaultNode.h"

class Position : public Component
{
public:
	Position();
	Position(DefaultNode* definer); // must go
	Position(Position&);

	virtual void getText(DefaultNode* def);
	virtual void get_data(DataSource* source);

	virtual Component* spawnCopy();
	virtual void move(int aX, int aY);

	virtual void handle(Event e);
protected:
	DataImpl<int>* x;
	DataImpl<int>* y;
};