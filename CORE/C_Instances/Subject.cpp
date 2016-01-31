#include "Subject.h"
#include "Commands.h"
#include "ObjectManager.h"
#include "VideoManager.h"
#include "AudioManager.h"


void walkForwardButtonPressed::execute()
{
	ObjectManager::enqueue(new walkForwardCommand());
}

void walkBackwardButtonPressed::execute()
{
	ObjectManager::enqueue(new walkBackwardCommand());
}

void walkLeftButtonPressed::execute()
{
	ObjectManager::enqueue(new walkLeftCommand());
}

void walkRightButtonPressed::execute()
{
	ObjectManager::enqueue(new walkRightCommand());
}
