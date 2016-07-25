#pragma once
#include "SDL.h"
#include "pugixml.hpp"

class Room;

class Drawable
{
public:
	Drawable();
	Drawable(pugi::xml_node node);
	Drawable(pugi::xml_node node, Room* room);
	virtual void draw(SDL_Renderer* renderer) = 0;
	int zIndex = 1;
};