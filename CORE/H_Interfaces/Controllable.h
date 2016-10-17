#pragma once
#include <vector>
#include "Events.h"

class Room;

class Controllable
{
public:
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0) = 0;


	//std::vector<Controllable*>* controllableVector - The vector that this controllable will be added to
	Controllable(std::vector<Controllable*>* controllableVector);
	Controllable(Room* room);

	//Does nothing. Only use when the child class is owned
	Controllable();

	//Also does nothing. Just a placeholder so you don't keep coming back to see if it's implemented
	Controllable(Controllable&);

	virtual void addTo(Room*);
};