#pragma once
#pragma once
#include "Drawable.h"
#include "pugixml.hpp"
#include "VisibleElement.h"
#include "SDL.h"
#include <vector>

class Room;

class  CompositeDrawable: public Drawable
{
public:
	CompositeDrawable(pugi::xml_node node);
	CompositeDrawable(pugi::xml_node node, Room* room);

	CompositeDrawable(CompositeDrawable& other);
	CompositeDrawable(CompositeDrawable& other, Room* room);

	std::vector<VisibleElement*> elements;
	virtual void draw(SDL_Renderer* renderer)
	{
		for (int i = 0; i < elements.size(); i++)
		{
			elements[i]->draw(renderer);
		}
	}

	void move(int x, int y);
};