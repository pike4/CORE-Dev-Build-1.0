#include "Subject.h"
#include "Commands.h"
#include "ObjectManager.h"
#include "VideoManager.h"
#include "AudioManager.h"


void walkForwardButtonPressed::execute(int type)
{
	ObjectManager::enqueue(new walkForwardCommand(type));
}

void walkBackwardButtonPressed::execute(int type)
{
	ObjectManager::enqueue(new walkBackwardCommand(type));
}

void walkLeftButtonPressed::execute(int type)
{
	ObjectManager::enqueue(new walkLeftCommand(type));
}

void walkRightButtonPressed::execute(int type)
{
	ObjectManager::enqueue(new walkRightCommand(type));
}

void collisionEvent::execute()
{

}