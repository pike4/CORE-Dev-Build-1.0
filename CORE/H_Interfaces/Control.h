#pragma once
#include "BaseObject.h"
#include "Controllable.h"
#include "Visible.h"
#include "Updatable.h"
#include "SDL.h"
#include "pugixml.hpp"
#include "VisibleElement.h"

class Aggregate;
class MenuScreen;

class Control : public BaseObject, public Controllable, public Visible, public Updatable
{
public:
	SDL_Rect boundingBox;
	Control(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Visible*>* visibleVector);
	Control(pugi::xml_node node, Aggregate* parent);
	Control(pugi::xml_node node, MenuScreen* parent);
	Control(pugi::xml_node node);

	int getX();
	int getY();

	virtual void update();

	virtual void draw(SDL_Renderer* renderer);

private:
	virtual void mouseEnter() = 0;
	virtual void mouseLeave() = 0;
	virtual void mouseDown() = 0;
	virtual void mouseUp() = 0;

	bool isWithin(int x, int y);

	void getArgsFromNode(pugi::xml_node node);

	std::vector<VisibleElement*> elements;

	bool mouseHovering;
	bool mouseIsDown;
};