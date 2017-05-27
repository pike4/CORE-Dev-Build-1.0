#pragma once
#include "Events.h"

#include <vector>

/*
	Provides a common interface for an object to receive messages

	TODO: 
	Trying to move away from the *Manager and *able nomenclature. Should rename to 
	Listener or something similar.

	Change handleInput arguments to int* message, int size
*/

class Controllable
{
public:
	virtual void handleInput(int key, int upDown = 0, int x = 0, int y = 0) = 0;
};