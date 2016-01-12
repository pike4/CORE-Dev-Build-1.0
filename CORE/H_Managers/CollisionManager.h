#include "_Manager.h"
#include "Commands.h"

#pragma once


class CollisionManager : public Manager
{
public:
	static void update()
	{
		updateQueue();
	}
};