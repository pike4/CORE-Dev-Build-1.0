#include "Room.h"
#include "SystemManager.h"
#include "StateManager.h"

//Load room from node
Room::Room(pugi::xml_node node)
{
	getArgsFromNode(node);
}

//Load room from file
Room::Room(char* fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load(fileName);

	pugi::xml_node curNode = doc.first_child();

	if (strcmp(curNode.name(), "Room"))
	{
		if (!strcmp("", fileName))
		{
			fileName = "NO NAME GIVEN";
		}
		printf("Attempted to load Room from malformed xml file: %s", fileName);
		return;
	}

	curNode = curNode.first_child();

	getArgsFromNode(curNode);
}

void Room::getArgsFromNode(pugi::xml_node node)
{
	node = node.first_child();

	updateVector = new std::vector<Updatable*>;
	drawVector = new std::vector<Visible*>;
	objectVector = new std::vector<BaseObject*>;
	collidableVector = new std::vector<Collidable*>;
	controllableVector = new std::vector<Controllable*>;

	do
	{
		if (strcmp(node.name(), "objects") == 0)
		{
			char* objectFileName = (char*)node.first_child().value();

			if (strcmp(objectFileName, "") != 0)
			{
				SystemManager::loadGameObjects(objectFileName, objectVector, drawVector, updateVector, collidableVector, controllableVector);
			}
		}

		else if (!strcmp(node.name(), "name"))
		{
			name = node.first_child().value();
		}

		else if (!strcmp(node.name(), "w"))
		{
			std::string wStr = node.first_child().value();

			w = atoi(wStr.c_str());
		}

		else if (!strcmp(node.name(), "h"))
		{
			h = atoi(node.first_child().value());
		}
		node = node.next_sibling();
	} while (strcmp(node.name(), "") != 0);

	quadTree = new QuadTree(0, 0, 0, w, h, NULL);
	for (int x = 0; x < collidableVector->size(); x++)
	{
		if ((*collidableVector)[x] != NULL)
		{
			quadTree->insert((*collidableVector)[x]);
		}
	}
}

void Room::handleInput(int key, int posOrNeg, int x, int y)
{
	for (int i = 0; i < controllableVector->size(); i++)
	{
		if ((*controllableVector)[i] != NULL)
		{
			(*controllableVector)[i]->handleInput(key, posOrNeg, x, y);
		}
	}
}

void Room::draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < drawVector->size(); i++)
	{
		if ((*drawVector)[i] != NULL)
		{
			(*drawVector)[i]->draw(renderer);
		}
	}
}

void Room::update()
{
	for (int i = 0; i < updateVector->size(); i++)
	{
		if ((*updateVector)[i] != NULL)
		{
			(*updateVector)[i]->update();
		}
	}
}