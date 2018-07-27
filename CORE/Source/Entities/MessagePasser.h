#pragma once
#include "Controllable.h"
#include <map>
#include <vector>

class MessagePasser
{
public:

	void registerEvent(int opcode, Controllable* observer);

	void unregisterEvent(int opcode, Controllable* observer);

	void unregisterObserver(Controllable* observer);

protected:
	std::map<int, std::vector<Controllable*>> observers;
};