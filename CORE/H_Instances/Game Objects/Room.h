#pragma once
#include "Updatable.h"
#include "BaseObject.h"
#include "Visible.h"
#include "Collidable.h"
#include "QuadTree.h"
#include "Controllable.h"
#include "Drawable.h"
#include "Pugixml.hpp"
#include <vector>

class Room : public Updatable, public Drawable, public Controllable
{
public:

	std::vector<Updatable*>* updateVector;
	std::vector<Visible*>* drawVector;
	std::vector<BaseObject*>* objectVector;
	std::vector<Collidable*>* collidableVector;
	std::vector<Controllable*>* controllableVector;

	std::string name;

	void handleInput(int key, int posOrNeg = 0, int x = 0, int y = 0);

	void draw(SDL_Renderer* renderer);

	void update();

	Room(pugi::xml_node);
	Room(char* fileName);

	QuadTree* quadTree;

private:
	void getArgsFromNode(pugi::xml_node node);
	int w, h;
};