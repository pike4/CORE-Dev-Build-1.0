#pragma once
#include <stdlib.h>
#include <vector>
#include "QuadTree.h"
#include "Collidable.h"
#include "MenuScreen.h"
#include "Room.h"

#include <map>

struct reflection;

//Provides interface to various constructors to decouple types from other classes
namespace CORE_Factory
{
	//Generation
	Definer* generateDefiner(pugi::xml_node node);
	Control* generateControl(Definer* definer);
	VisibleElement* generateVisibleElement(Definer* definer);
	Component* generateComponent(Definer* definer);
	Entity* generateGameObject(Definer* definer);
	Entity* generateGameObject(Definer* definer, std::map<std::string, reflection>* parentInfo = NULL);
	Entity* generate(std::string prototypeName);

	Data* generateDataFromReflection(reflection a);
};