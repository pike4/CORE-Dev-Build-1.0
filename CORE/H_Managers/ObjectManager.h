#pragma once
#include <stdlib.h>
#include <vector>
#include "_Manager.h"
#include "Thing.h"
#include "Updatable.h"





class ObjectManager : public Manager
{
public:
	

	static void update();
	static void add(Thing* E);
	static void addUpdatable(Updatable* E);
	static int getObjectCount();
	static std::vector <BaseObject*>* getObjectVector();

	static Mobile* player;

private:

	static std::vector <Updatable*> UpdateVector;
	static std::vector <BaseObject*> BaseObjectVector;
};
