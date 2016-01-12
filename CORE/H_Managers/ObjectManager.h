#pragma once
#include <stdlib.h>
#include <vector>

#include "Thing.h"
#include "Updatable.h"





class ObjectManager
{
public:
	

	static void update();
	static void add(Thing* E);
	static void addUpdatable(Updatable* E);

private:

	static std::vector <Updatable*> UpdateVector;
	static std::vector <BaseObject*> BaseObjectVector;
};
