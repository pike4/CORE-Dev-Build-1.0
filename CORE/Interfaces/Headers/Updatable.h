#pragma once
#include <vector>
#include "Component.h"

class Room;

class Updatable
{
public:
	virtual void update() = 0;
	virtual void add(Room*);
	Updatable();
	Updatable(std::vector<Updatable*>*);
	Updatable(Room* room);
	~Updatable();
};