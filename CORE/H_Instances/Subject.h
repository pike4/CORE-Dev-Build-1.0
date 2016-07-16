#pragma once
#include "_Manager.h"
#include "Controllable.h"
#include <vector>

class Subject : public Controllable
{
public:
	void addObserver(Controllable* observer)
	{
		observers.push_back(observer);
	}

	/*Remove the observer at the pointer
	Returns:
	0: Observer was present and was removed
	-1: Observer was not present*/
	int removeObserver(Controllable* observer)
	{
		for (int i = 0; i < observers.size(); i++)
		{
			if (observers[i] == observer)
			{
				observers.erase(observers.begin() + i);
				return 0;
			}
		}
		return -1;
	}

	/*Remove the observer at the specified index
	0: Index was within bounds
	-1: Index was out of bounds*/
	int removeObserver(int index)
	{
		if (index < observers.size() && index >= 0)
		{
			observers.erase(observers.begin() + index);
			return 0;
		}
		return -1;
	}


	void handleInput(int keyCode, int upDown = 0, int x = 0, int y = 0)
	{
		for (int i = 0; i < observers.size(); i++)
		{
			observers[i]->handleInput(keyCode, upDown, x, y);
		}
	}

private:
	std::vector<Controllable*> observers;
};