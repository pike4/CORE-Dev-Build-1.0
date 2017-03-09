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

	for (unsigned int i = 0; i < list->size(); i++)
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
void Observer::handleInput(int key, int upDown, int x, int y)
{
	if (listeners.find(key) == listeners.end())
	{
		//TODO
		//warning: key not found
		return;
	}

	std::vector<Controllable*> listenerList = *(listeners[key]);

	for (unsigned int i = 0; i < listenerList.size(); i++)
	{
		listenerList[i]->handleInput(key, upDown, x, y);
	}
}