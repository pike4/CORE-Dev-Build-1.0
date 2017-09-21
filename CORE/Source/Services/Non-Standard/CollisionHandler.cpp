#include "CollisionHandler.h"
#include "CORE.h"
#include "CORE_Resources.h"

void CollisionHandler::accept(BoundingBox* box)
{
   boundingBoxes.push_back(box);
}

void CollisionHandler::handle(Event e)
{
   Event getBBEvent(CORE_Resources::getEventCode("getBoundingBox"));
   EventArg a = this;
   getBBEvent.arguments.push_back(a);

   switch (e.opcode)
   {
   case entity_added:
      CORE::currentRoom->handle(getBBEvent);
      break;
   case updateStep:
      update();
      break;
   }
}

bool CollisionHandler::isOverlapping(BoundingBox* r1, BoundingBox* r2)
{
   int x1, y1, w1, h1, x2, y2, w2, h2;

   x1 = *r1->x;
   y1 = *r1->y;
   w1 = *r1->w;
   h1 = *r1->h;
          
   x2 = *r2->x;
   y2 = *r2->y;
   w2 = *r2->w;
   h2 = *r2->h;

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

void CollisionHandler::update()
{
   for (int i = 0; i < boundingBoxes.size(); i++)
   {
      for (int j = 0; j < boundingBoxes.size(); j++)
      {
         if (i != j)
         {
            if (isOverlapping(boundingBoxes[i], boundingBoxes[j]))
            {
               int a = 0;
               CORE_SystemIO::error("woah there two objects are colliding!");
            }
         }
      }
   }
}