#pragma once
#include <stdlib.h>
#include <vector>
#include "_Manager.h"
#include "Thing.h"
#include "Player.h"
#include "Updatable.h"
#include "QuadTree.h"
#include "Collidable.h"

class ObjectManager : public Manager
{
public:
	static int state;

	static void update();

	static void updateRunning();
	static void updateInMenu();
	static void updatePaused();
	static void updateBlocking();

	static void goToBlocking();
	static void goToPaused();
	static void goToRunning();
	static void goToInMenu();

	static void handleMouseClick();

	static void add(BaseObject* E);
	static void start();
	static void stop();
	static void addCollidable(Collidable* C);
	static void addUpdatable(Updatable* E);
	static void removeUpdatable(Updatable* E);
	static int getObjectCount();
	static std::vector <BaseObject*>* getObjectVector();
	static QuadTree quadTree;

	static SDL_Renderer* testRenderer;
	static Player* player;

private:

	static std::vector <Updatable*> UpdateVector;
	static std::vector <BaseObject*> BaseObjectVector;


};
