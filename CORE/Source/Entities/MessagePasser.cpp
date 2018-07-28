#include "MessagePasser.h"

void MessagePasser::registerEvent(int opcode, Controllable* observer)
{
	if (observers.find(opcode) == observers.end())
	{
		observers[opcode] = std::vector<Controllable*>();
	}
	std::vector<Controllable*> opvec = observers[opcode];
	observers[opcode].push_back(observer);
}

void MessagePasser::unregisterEvent(int opcode, Controllable* observer)
{
	if (observers.find(opcode) != observers.end())
	{
		for (int i = 0; i < observers[opcode].size(); i++)
		{
			if (observers[opcode][i] == observer) 
			{
				observers[opcode].erase(observers[opcode].begin() + i);
			}
		}
	}
}

void MessagePasser::unregisterObserver(Controllable* observer)
{
	for (std::map<int, std::vector<Controllable*>>::iterator it = observers.begin(); it != observers.end(); ++it)
	{
		unregisterEvent(it->first, observer);
	}
}