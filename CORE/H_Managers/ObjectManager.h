#pragma once
#include <stdlib.h>
#include <vector>
#include "_Manager.h"
#include "Thing.h"
#include "Player.h"
#include "Updatable.h"





class ObjectManager : public Manager
{
public:
	

	static void update();
	static void add(BaseObject* E);
	static void start();
	static void addUpdatable(Updatable* E);
	static int getObjectCount();
	static std::vector <BaseObject*>* getObjectVector();

	static Player* player;

private:

	static std::vector <Updatable*> UpdateVector;
	static std::vector <BaseObject*> BaseObjectVector;
};
