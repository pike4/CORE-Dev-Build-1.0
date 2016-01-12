#pragma once
#include "Commands.h"
#include <queue>

class Manager
{
public:
	virtual void update() = 0;

	virtual void start() = 0;

	virtual void stop() = 0;

	static void enqueue(Command* command);

	static void updateQueue();

protected:
	static std::queue <Command*> mQueue;
};

