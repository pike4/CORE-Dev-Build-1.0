#pragma once
#include "Drawable.h"
#include "pugixml.hpp"
#include "Room.h"
#include "VisibleElement.h"
#include "SDL.h"

class SimpleDrawable : public Drawable
{
public:
	SimpleDrawable(pugi::xml_node node);
	SimpleDrawable(pugi::xml_node node, Room* room);

	VisibleElement* element;
	virtual void draw(SDL_Renderer* renderer)
	{
		element->draw(renderer);
	}
};