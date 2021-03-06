#pragma once
#include <map>
#include <vector>
#include "Controllable.h"


class Observer : public Controllable
{
public:
	std::map<int, std::vector<Controllable*>*> listeners;

	int registerListener(int key, Controllable* controllable);
	int deregisterListener(int key, Controllable* listener);

   virtual void handle(Event e);
};