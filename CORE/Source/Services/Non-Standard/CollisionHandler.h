#pragma once
#include "BoundingBoxAccepter.h"
#include "Entity.h"

#include <vector>

class CollisionHandler : public BoundingBoxAccepter, public Entity
{
public:

   virtual void handle(Event e);

   virtual void accept(BoundingBox* box);

   std::vector<BoundingBox*> boundingBoxes;

private:
   bool isOverlapping(BoundingBox* b1, BoundingBox* b2);
   void update();
};