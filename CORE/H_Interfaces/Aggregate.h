#pragma once
#include <vector>
#include "Control.h"
#include "pugixml.hpp"
#include "MenuScreen.h"

class Aggregate : public Control
{
public:
	Aggregate(pugi::xml_node node, MenuScreen* parent) : Control(node, parent)
	{
		getArgsFromNode(node);
	}

	Aggregate(pugi::xml_node node, Aggregate* parent) : Control(node, parent)
	{
		getArgsFromNode(node);
	}

	void addChild(Control* child)
	{
		children.push_back(child);
	}

	/*Remove the child at the pointer
	Returns:
	0: Child was present and was removed
	-1: Child was not present*/
	int removeChild(Control* child)
	{
		for (int i = 0; i < children.size(); i++)
		{
			if (children[i] == child)
			{
				children.erase(children.begin() + i);
				return 0;
			}
		}
		return -1;
	}

	/*Returns:
	0: Index was within bounds
	-1: Index was out of bounds*/
	int removeChild(int index)
	{
		if (index < children.size() && index >= 0)
		{
			children.erase(children.begin() + index);
			return 0;
		}
		return -1;
	}

	void handleInput(int key, int upDown = 0, int x = 0, int y = 0)
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[x]->handleInput(key, upDown, x, y);
		}
		selfHandleInput(key, upDown, x, y);
	}

	void draw(SDL_Renderer* renderer)
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[x]->draw(renderer);
		}
	}
private:
	//Use this to implement any input response specific to the aggregate
	virtual void selfHandleInput(int key, int upDown = 0, int x = 0, int y = 0) = 0;
	std::vector<Control*> children;
	void getArgsFromNode(pugi::xml_node node);
};