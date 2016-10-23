#pragma once
#include "SDL.h"
#include "pugixml.hpp"
#include "Component.h"

class Room;

class Drawable
{
public:
	Drawable();
	Drawable(pugi::xml_node node);
	Drawable(pugi::xml_node node, Room* room);
	virtual void draw() = 0;
	virtual void add(Room*);
	int zIndex = 1;
};