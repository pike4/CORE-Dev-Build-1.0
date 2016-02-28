#include "Updatable.h"
#include "ObjectManager.h"

Updatable::Updatable()
{
	ObjectManager::addUpdatable(this);
}

Updatable::~Updatable()
{
	ObjectManager::removeUpdatable(this);
}