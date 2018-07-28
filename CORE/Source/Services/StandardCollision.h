#pragma once
#include "Handler.h"
#include "BoundingBox.h"

class StandardCollision : public Handler
{
public:
	StandardCollision();
	virtual void handle(Event e);


protected:
	virtual void add(Entity* newEntity);

	std::vector<BoundingBox> boundingBoxes;
};