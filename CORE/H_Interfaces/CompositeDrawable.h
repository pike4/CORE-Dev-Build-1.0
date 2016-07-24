#pragma once
#pragma once
#include "Drawable.h"
#include "pugixml.hpp"
#include "Room.h"
#include "VisibleElement.h"
#include "SDL.h"
#include <vector>

class  CompositeDrawable: public Drawable
{
public:
	CompositeDrawable(pugi::xml_node node);
	CompositeDrawable(pugi::xml_node node, Room* room);

	std::vector<VisibleElement*> elements;
	virtual void draw(SDL_Renderer* renderer)
	{
		for (int i = 0; i < elements.size(); i++)
		{
			elements[i]->draw(renderer);
		}
	}
};