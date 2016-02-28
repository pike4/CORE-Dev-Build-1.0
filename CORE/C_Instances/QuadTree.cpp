#include "QuadTree.h"
#include "Collidable.h"
#include <vector>

QuadTree::QuadTree(int aDepth, int x, int y, int width, int height, QuadTree* aParent)
{
	currentDepth = aDepth;
	frame.w = width;
	frame.h = height;
	frame.x = x;
	frame.y = y;
	parent = aParent;
}

#pragma region Update methods
void QuadTree::update()
{
	reorganize();
	checkCollisions();
}
//Remember that this method does not check the object vector against those of its children, but recursively has
//those children check against their parents
void QuadTree::checkCollisions()
{
	//If there are child trees, check those first
	if (subTrees[0] != NULL)
	{
		//A parent always puts the child's needs ahead of their own
		for (int x = 0; x < 4; x++)
		{
			subTrees[x]->checkCollisions();
		}
	}

	//Then check this QuadTree's objects against everything belonging to its ancestors
	if (parent != NULL)
	{
		parentCheck(objectsInTree, parent);
	}

	selfCheck(objectsInTree);
}

//Recursively check all objects in this node against all objects in each parent node up to and including the root
void QuadTree::parentCheck(std::vector<Collidable*> objectsToCheck, QuadTree* parent)
{
	//Check against the parent
	checkAgainst(this->objectsInTree, parent->objectsInTree);

	//Then check against grandpa
	if (parent->parent != NULL)
	{
		parentCheck(objectsToCheck, parent->parent);
	}
}

//Check all elements in the vector against all other elements in the vector
void QuadTree::selfCheck(std::vector<Collidable*> vectorToCheck)
{
	for (int i = 0; i < vectorToCheck.size(); i++)
	{
		Collidable* obj1 = vectorToCheck[i];
		for (int j = 0; j < vectorToCheck.size(); j++)
		{
			Collidable* obj2 = vectorToCheck[j];
			if (QuadTree::isOverlapping(obj1->boundingBox, obj2->boundingBox) && (i != j))
			{
				printf("IT FUCKING WORKS");
				break;
			}
		}
	}
}

void QuadTree::checkAgainst(std::vector<Collidable*> v1, std::vector<Collidable*> v2)
{
	for each(Collidable* obj1 in v1)
	{
		for each(Collidable* obj2 in v2)
		{
			if (QuadTree::isOverlapping(obj1->boundingBox, obj2->boundingBox))
			{
				//Handle the collision
			}
		}
	}
}

#pragma endregion


#pragma region Reorganizing methods
void QuadTree::insert(Collidable* objectToAdd)
{
	if (subTrees[0] != NULL)
	{
		for (int x = 0; x < 4; x++)
		{
			if (isWithin(objectToAdd->boundingBox, subTrees[x]->frame))
			{
				subTrees[x]->insert(objectToAdd);
			}
			return;
		}
	}

	objectsInTree.push_back(objectToAdd);
}
//Remove a Collidable from the current QuadTree
void QuadTree::remove(Collidable* objectToRemove)
{
	for (int i = 0; i < objectsInTree.size(); i++)
	{
		if (objectsInTree[i] == objectToRemove)
		{
			objectsInTree.erase(objectsInTree.begin() + i, objectsInTree.begin() + i + 1);
		}
	}
}

//Remove a Collidable and move the iterator back so that nothing gets skipped over due to the vector changing size
void QuadTree::remove(Collidable* objectToRemove, int* iter)
{
	remove(objectToRemove);
	
	if (iter != NULL)
	{
		*iter -= 1;
	}
}

//Completely remove a Collidable from the collision system 
void QuadTree::destroyCollidable(Collidable* objectToRemove)
{
	if(subTrees[0] != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			if (isWithin(objectToRemove->boundingBox, subTrees[i]->frame))
			{
				subTrees[i]->destroyCollidable(objectToRemove);
				return;
			}
		}
		//Only called if object is not in any subtree, or, it is in the current node
		delete(objectToRemove);
		remove(objectToRemove);
		
	}

	else
	{
		//If we have gotten this deep and the object is still not found, it must be in this node
		delete(objectToRemove);
		remove(objectToRemove);
	}
}

//Give the current node 4 children and send down any objects that fit into the children
void QuadTree::split()
{
	if (subTrees[0] != NULL)
	{
		return;
	}

	subTrees[0] = new QuadTree(currentDepth, frame.x, frame.y, frame.w / 2, frame.h / 2, this);
	subTrees[1] = new QuadTree(currentDepth, frame.x + frame.w / 2, frame.y, frame.w / 2, frame.h / 2, this);
	subTrees[2] = new QuadTree(currentDepth, frame.x, frame.y + frame.h / 2, frame.w / 2, frame.h / 2, this);
	subTrees[3] = new QuadTree(currentDepth, frame.x + frame.w / 2, frame.y + frame.h / 2, frame.w / 2, frame.h / 2, this);

	for (int i = 0; i < objectsInTree.size(); i++)
	{
		Collidable* obj = objectsInTree[i];
		for (int x = 0; x < 4; x++)
		{
			if (isWithin(obj->boundingBox, subTrees[x]->frame))
			{
				subTrees[x]->insert(obj);
				remove(obj, &i);
				break;
			}
		}

	}
}

//Send all Collidables in the children to the current node and kill children
void QuadTree::merge()
{
	for (int i = 0; i < 4; i++)
	{
		for each(Collidable* childObject in subTrees[i]->objectsInTree)
		{
			objectsInTree.push_back(childObject);
		}
		delete subTrees[i];
		subTrees[i] = NULL;
	}
}

//Get count of objects in current node
int QuadTree::getObjectCount()
{
	return objectsInTree.size();
}

//Get the count of objects in the current node and all children
int QuadTree::getRecursiveObjectCount()
{
	int total = 0;
	int y = 0;

	if (subTrees[0] != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			total += subTrees[i]->getRecursiveObjectCount();
		}

		total += objectsInTree.size();

		return total;
	}

	else return objectsInTree.size();
}

/*Merge all trees that have fewer than MAX_OBJECTS  berween them, split any nodes that have more than MAX_OBJECTS, and send any objects that have moved out to the parents*/
void QuadTree::reorganize()
{
	if (subTrees[0] != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			subTrees[i]->reorganize();
		}

		if (getRecursiveObjectCount() <= MAX_OBJECTS)
		{
			merge();
		}
	}

	else if (objectsInTree.size() >= MAX_OBJECTS && currentDepth < MAX_DEPTH)
	{
		split();
	}

	//Send any objects that fit into the children down
	if (subTrees[0] != NULL)
	{
		
		for (int j = 0; j < objectsInTree.size(); j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (isWithin(objectsInTree[j]->boundingBox, subTrees[i]->frame))
				{
					subTrees[i]->insert(objectsInTree[j]);
					remove(objectsInTree[j], &j);
					break;
				}
			}
		}
	}

	//Once their are no children to deal with, send any objects that have moved out to the parent
	for (int i = 0; i < objectsInTree.size(); i++)
	{
		Collidable* obj = objectsInTree[i];
		if (!isWithin(obj->boundingBox, frame))
		{
			if (parent != NULL)
			{
				parent->insert(obj);
				remove(obj, &i);
			}
		}
	}
}

#pragma endregion

#pragma region Collision Checking Methods
//Check if there is any overlap between r1 and r2
bool QuadTree::isOverlapping(SDL_Rect r1, SDL_Rect r2)
{
	return(((r1.x + r1.w) > r2.x) && (r1.x < (r2.x + r2.w)) && ((r1.y + r1.h) > r2.y) && (r1.y < (r2.y + r2.h)));
}

//Check if r1 is completely within r2
bool QuadTree::isWithin(SDL_Rect r1, SDL_Rect r2)
{
	return ((r1.x > r2.x) && ((r1.x + r1.w) < (r2.x + r2.w)) && (r1.y > r2.y) && ((r1.y + r1.h) < (r2.y + r2.h)));
}
#pragma endregion