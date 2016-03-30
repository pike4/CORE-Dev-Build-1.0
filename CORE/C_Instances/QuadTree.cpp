#include "QuadTree.h"
#include "Collidable.h"
#include "VideoManager.h"
#include "ObjectManager.h"
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

	drawRects[0].x = frame.x;
	drawRects[0].y = frame.y;
	drawRects[0].w = frame.w;
	drawRects[0].h = 10;

	drawRects[1].x = frame.x;
	drawRects[1].y = frame.y;
	drawRects[1].w = 10;
	drawRects[1].h = frame.h;

	drawRects[2].x = frame.x + frame.w;
	drawRects[2].y = frame.y;
	drawRects[2].w = -10;
	drawRects[2].h = frame.h;

	drawRects[3].x = frame.x;
	drawRects[3].y = frame.y + frame.h;
	drawRects[3].w = frame.w;
	drawRects[3].h = -10;



	if (true)
	{
		for (int x = 0; x < 4; x++)
		{
			VideoManager::enqueue(new DrawRectCommand(drawRects[x]));
		}
	}
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
			
			if (i != j)
			{
				if (testPairCollision(obj1, obj2))
				{
					printf("Collision Detected\n");
					obj1->onCollide(obj2);
					obj2->onCollide(obj1);
				}

				else
				{
					printf("\nNo Collision was detected\n");
				}
			}
		}
	}
}

void QuadTree::checkAgainst(std::vector<Collidable*> v1, std::vector<Collidable*> v2)
{
	for (int i = 0; i < v1.size(); i++)
	{
		Collidable* obj1 = v1[i];
		for (int j = 0; j < v2.size(); j++)
		{
			Collidable* obj2 = v2[j];
			if (i != j)
			{
				if (testPairCollision(obj1, obj2))
				{
					printf("Collision detected in parent\n");
				}

				else
				{
					printf("No collision was detected in the parent\n");
				}
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
				return;
			}
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

		if (getRecursiveObjectCount() < MAX_OBJECTS)
		{
			int a = MAX_OBJECTS;
			merge();
		}
	}

	else if (objectsInTree.size() >= MAX_OBJECTS && currentDepth < MAX_DEPTH)
	{
		int a = MAX_OBJECTS;
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
	int x1, y1, w1, h1, x2, y2, w2, h2;

	x1 = r1.x;
	y1 = r1.y;
	w1 = r1.w;
	h1 = r1.h;

	x2 = r2.x;
	y2 = r2.y;
	w2 = r2.w;
	h2 = r2.h;

	if (w1 < 0)
	{
		x1 = x1 + w1;
		w1 *= -1;
	}

	if (h1 < 0)
	{
		y1 = y1 + h1;
		h1 *= -1;
	}

	if (w2 < 0)
	{
		x2 = x2 + w2;
		w2 *= -1;
	}

	if (h2 < 0)
	{
		y2 = y2 + h2;
		h2 *= -1;
	}


	return(((x1 + w1) >= x2) && (x1 <= (x2 + w2)) && ((y1 + h1) >= y2) && (y1 <= (y2 + h2)));
}

//Check if r1 is completely within r2
bool QuadTree::isWithin(SDL_Rect r1, SDL_Rect r2)
{
	return ((r1.x > r2.x) && ((r1.x + r1.w) < (r2.x + r2.w)) && (r1.y > r2.y) && ((r1.y + r1.h) < (r2.y + r2.h)));
}

bool QuadTree::PositionVectorIntersect(Collidable* obj1, Collidable* obj2)
{
	int obj1AXobj2 = crossProduct(obj1, *obj2->prevXPtr, *obj2->prevYPtr);
	int obj1BXobj2 = crossProduct(obj1, obj2->boundingBox.x, obj2->boundingBox.y);

	if (obj1BXobj2 == 0 && obj1AXobj2 == 0)
	{
		if ((obj1->boundingBox.y - *(obj1->prevYPtr) == 0) && (obj2->boundingBox.y - *(obj2->prevYPtr) == 0))
		{
			if (obj1->boundingBox.y == obj2->boundingBox.y)
			{
				if(obj1->boundingBox.x > *obj2->prevXPtr && *obj1->prevXPtr < obj2->boundingBox.x)
				{
					return true;
				}
			}
		}
	}

	bool obj1AIsRightOfObj2Vector = obj1AXobj2 > 0;
	bool obj1BIsRightOfObj2Vector = obj1BXobj2 > 0;

	bool obj2PointstoObj1 = obj1AIsRightOfObj2Vector != obj1BIsRightOfObj2Vector;

	bool obj2AIsRightOfObj1Vector = crossProduct(obj2, *obj1->prevXPtr, *obj1->prevYPtr) > 0;
	bool obj2BIsRightOfObj1Vector = crossProduct(obj2, obj1->boundingBox.x, obj2->boundingBox.y) > 0;

	bool obj1PointsToObj2 = obj2AIsRightOfObj1Vector != obj2BIsRightOfObj1Vector;


	return obj2PointstoObj1 && obj1PointsToObj2;
}

bool QuadTree::testPairCollision(Collidable* obj1, Collidable* obj2)
{
	if (isOverlapping(obj1->boundingBox, obj2->boundingBox))
	{
		return true;
	}

	else if (isOverlapping(obj1->movementVector, obj2->movementVector))
	{
		printf("Position Box intersection\t");
		if (PositionVectorIntersect(obj1, obj2))
		{
			printf("Vector have crossed\t");
			return true;
		}
	}

	return false;
}

int QuadTree::crossProduct(Collidable* obj1, int x, int y)
{
	return ((obj1->boundingBox.x - *(obj1->prevXPtr)) * (y - obj1->boundingBox.y)) - ((obj1->boundingBox.y - *(obj1->prevYPtr)) * (x - obj1->boundingBox.x));
}
#pragma endregion