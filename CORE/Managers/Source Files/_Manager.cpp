#include "_Manager.h"

void Manager::enqueue(Command* command)
{
	mQueue.push(command);
}

void Manager::updateQueue()
{
	while (!mQueue.empty())
	{
		Command * C = mQueue.front();

		C->execute();

		mQueue.pop();
	}
}

std::queue <Command*> Manager::mQueue;