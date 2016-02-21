#pragma once
#include "SDL.h"
#include "Collidable.h"
#include <vector>

/*
A recursive class used to check collisions. Splits the area being observed into quadrants
so that objects in each quadrant only need to be compared with objects in that quadrant and 
its parent to combat n^2 complexity
*/
class QuadTree
{
public:
	
	QuadTree(int, int x, int y, int w, int h, QuadTree* parent);
	void split();
	void insert(Collidable*);
	void remove(Collidable*);
	void destroyCollidable(Collidable*);
	void update();

	int getObjectCount();

	int getRecursiveObjectCount();

	static bool isWithin(SDL_Rect r1, SDL_Rect r2);

	static bool isOverlapping(SDL_Rect r1, SDL_Rect r2);
	
private:
	//Merge QuadTrees with fewer than MAX_OBJECTS in their parent and split cells with greater
	//than MAX_OBJECTS
	void reorganize();

	//Check collisions for this QuadTree against itself and ancestors. 
	void checkCollisions();

	static const int MAX_DEPTH = 5;

	//Number of objects that can be in any given 
	static const int MAX_OBJECTS = 10;

	//The number of levels from the top where this QuadTree is located
	int currentDepth;

	//Contains the coordinates and size of the QuadTree
	SDL_Rect frame;

	//Recursively check for collisions with objects in all parent trees up to and including the root
	void parentCheck(std::vector<Collidable*> objectsToCheck, QuadTree* parent);

	//Check all objects in the current node against one another for collisions
	//void currentNodeCheck();

	//Check all elements in the given vector against each other
	void selfCheck(std::vector<Collidable*> vectorToCheck);

	//Check all elements in v1 against all elements in v2
	void checkAgainst(std::vector<Collidable*> v1, std::vector<Collidable*> v2);

	//Pointer to parent QuadTree
	QuadTree* parent;

	void merge();

	//Pointers to child trees
	QuadTree* subTrees [4];

	//The collidables that fit within this QuadTree
	std::vector<Collidable*> objectsInTree;
};