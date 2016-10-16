#pragma once
#include <stdlib.h>
#include <vector>
#include <map>
#include "_Manager.h"
#include "Player.h"
#include "Updatable.h"
#include "QuadTree.h"
#include "Collidable.h"
#include "MenuScreen.h"
#include "Room.h"

class ObjectManager : public Manager
{
public:
	//Update
	static void update();

	static void updateRunning();
	static void updateInMenu();
	static void updatePaused();
	static void updateBlocking();

	//State
	static void goToBlocking();
	static void goToPaused();
	static void goToRunning();
	static void goToInMenu();
	static int state;

	static void handleMouseClick();

	static void add(BaseObject* E);
	static void start();
	static void stop();
	static void addCollidable(Collidable* C);
	static void addUpdatable(Updatable* E);
	static void removeUpdatable(Updatable* E);
	static int getObjectCount();

	//Generation
	static Control* generateControl(std::string controlType, pugi::xml_node node);
	static VisibleElement* generateVisibleElement(std::string controlType, pugi::xml_node node);

	static GameObject* generateGameObject(std::string, pugi::xml_node node, Room* room);
	static GameObject* generateGameObject(std::string, pugi::xml_node node);
	static GameObject* generate(std::string prototypeName);
	static GameObject* spawn(std::string prototypeName, Room* room);

	static void handleEvent(int eventCode, int posOrNeg = 0, int x = 0, int y = 0);

	static std::vector <BaseObject*>* getObjectVector();
	static std::vector <Updatable*>* getUpdateVector();

	static void setObjectVector(std::vector<BaseObject*>* newVector);
	static void setUpdateVector(std::vector<Updatable*>* newVector);
	static QuadTree quadTree;

	static Room* currentRoom;

	static SDL_Renderer* testRenderer;
	static Cursor* mouse;
	static MenuScreen* currentGUI;
	static MenuScreen gui;

	static std::map<std::string, MenuSystem*> menuSystems;

private:

	static std::vector <Updatable*>* UpdateVector;
	static std::vector <BaseObject*>* BaseObjectVector;
};