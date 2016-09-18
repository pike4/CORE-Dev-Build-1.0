#include "Room.h"
#include "SystemManager.h"
#include "StateManager.h"
#include "ObjectManager.h"
#include "GameObject.h"

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

#pragma region adders and removers

void Room::add(GameObject* object)
{
	for (int i = 0; i < object->components.size(); i++)
	{
		object->components[i]->addTo(this);
	}

	if (object->isControllable())
	{
		controllableVector->push_back(object);
	}

	if (object->isUpdatable())
	{
		updateVector->push_back(object);
	}
}
void Room::add(Updatable* component)
{
	updateVector->push_back(component);
}
void Room::add(Drawable*component)
{
	drawVector->push_back(component);
}
void Room::add(BaseObject* component)
{
	objectVector->push_back(component);
}
void Room::add(Collidable* component)
{
	collidableVector->push_back(component);
}
void Room::add(Controllable* component)
{
	controllableVector->push_back(component);
}

void Room::remove(Updatable* component)
{
	for (int i = 0; i < updateVector->size(); i++)
	{
		if ((*updateVector)[i] == component)
		{
			updateVector->erase(updateVector->begin() + i, updateVector->begin() + i);
			return;
		}
	}

	//TODO:
	//Log warning: component not found
}
void Room::remove(Drawable* component)
{
	for (int i = 0; i < drawVector->size(); i++)
	{
		if ((*drawVector)[i] == component)
		{
			drawVector->erase(drawVector->begin() + i, drawVector->begin() + i);
			return;
		}
	}

	//TODO:
	//Log warning: component not found
}
void Room::remove(BaseObject* component)
{
	for (int i = 0; i < objectVector->size(); i++)
	{
		if ((*objectVector)[i] == component)
		{
			objectVector->erase(objectVector->begin() + i, objectVector->begin() + i);
			return;
		}
	}

	//TODO:
	//Log warning: component not found
}
void Room::remove(Collidable *component)
{
	for (int i = 0; i < collidableVector->size(); i++)
	{
		if ((*collidableVector)[i] == component)
		{
			collidableVector->erase(collidableVector->begin() + i, collidableVector->begin() + i);
			return;
		}
	}

	//TODO:
	//Log warning: component not found
}
void Room::remove(Controllable* component)
{
	for (int i = 0; i < controllableVector->size(); i++)
	{
		if ((*controllableVector)[i] == component)
		{
			controllableVector->erase(controllableVector->begin() + i, controllableVector->begin() + i);
			return;
		}
	}

	//TODO:
	//Log warning: component not found
}

#pragma endregion

void Room::spawn(std::string objectName)
{
	if (objectName.empty())
	{
		return;
	}

	GameObject* newObject = ObjectManager::generate(objectName);

	add(newObject);
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