#pragma once
#include "Events.h"
#include "Event.h"

#include <vector>


class Controllable
{
public:
	virtual void handle(Event e) = 0;
};