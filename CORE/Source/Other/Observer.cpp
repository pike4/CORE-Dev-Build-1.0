#include "Observer.h"

//Register the given listener to listen for the given event key
int Observer::registerListener(int key, Controllable* listener)
{
	if (listeners.find(key) == listeners.end())
	{
		listeners[key] = new std::vector<Controllable*>;
	}

	listeners[key]->push_back(listener);

	return 1;
}

int Observer::deregisterListener(int key, Controllable* listener)
{
	if (listeners.find(key) == listeners.end())
	{
		//Event does not exist
		return 0;
	}

	std::vector<Controllable*>* list = listeners[key];

	for (int i = 0; i < list->size(); i++)
	{
		if (listener == (*list)[i])
		{
			list->erase(list->begin() + i);
			return 1;
		}
	}

	//Element was not found
	return 0;
}

//Pass the given event key to all listeners who are listening for it
void Observer::handle(Event e)
{
	if (listeners.find(e.opcode) == listeners.end())
	{
		//TODO
		//warning: key not found
		return;
	}

	std::vector<Controllable*> listenerList = *(listeners[e.opcode]);

	for (int i = 0; i < listenerList.size(); i++)
	{
		listenerList[i]->handle(e);
	}
}