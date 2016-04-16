#include "Updatable.h"
#include "ObjectManager.h"

Updatable::Updatable()
{
	ObjectManager::addUpdatable(this);
}

Updatable::Updatable(std::vector<Updatable*>* updateVec)
{
	updateVec->push_back(this);
}

Updatable::~Updatable()
{
	ObjectManager::removeUpdatable(this);
}