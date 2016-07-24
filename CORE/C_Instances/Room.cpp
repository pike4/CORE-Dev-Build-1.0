#include "Room.h"
#include "SystemManager.h"
#include "StateManager.h"
#include "ObjectManager.h"

//Load room from node
Room::Room(pugi::xml_node node)
{
	getArgsFromNode(node);
}

//Load room from file
Room::Room(std::string fileName)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load(fileName.c_str());

	pugi::xml_node curNode = doc.first_child();

	if (strcmp(curNode.name(), "Room"))
	{
		if (fileName.empty())
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
	drawVector = new std::vector<Drawable*>;
	objectVector = new std::vector<BaseObject*>;
	collidableVector = new std::vector<Collidable*>;
	controllableVector = new std::vector<Controllable*>;

	do
	{
		if (strcmp(node.name(), "objects") == 0)
		{
			pugi::xml_node objectsNode = node.first_child();
			std::string curName = objectsNode.name();

			while (!curName.empty())
			{
				ObjectManager::generateGameObject(curName, objectsNode, this);
				objectsNode = objectsNode.next_sibling();
				curName = objectsNode.name();
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

// 7/2016 compliant
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

//Draw every drawable in the room. 7/2016 compliant
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
// 7/2016 compliant
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