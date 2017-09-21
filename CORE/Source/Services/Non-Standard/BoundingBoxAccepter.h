#pragma once
#include "BoundingBox.h"

class BoundingBoxAccepter
{
public:
   virtual void accept(BoundingBox*) = 0;
};