#pragma once
#include <vector>

class Room;

class Updatable
{
public:
	virtual void update() = 0;
	Updatable();
	Updatable(std::vector<Updatable*>*);
	Updatable(Room* room);
	~Updatable();
};