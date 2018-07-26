#include "StandardCollision.h"

void StandardCollision::handle(Event e)
{
	Handler::handle(e);

	switch (e.opcode)
	{
	case updateStep:
		for (int i = 0; i < boundingBoxes.size(); i++)
		{
			for (int j = i; j < boundingBoxes.size(); j++)
			{
				if (i == j) continue;

				BoundingBox a = boundingBoxes[i];
				BoundingBox b = boundingBoxes[j];

				if (*a.x + *a.w > *b.x
					&& *a.x < *b.x + *b.w
					&& *a.y < *b.y + *b.h
					&& *a.y + *a.h > *b.y)
				{
					printf("collision\n");
				}
			}
		}
		break;
	}
}

void StandardCollision::add(Entity* newEntity)
{
	boundingBoxes.push_back(
	{
		newEntity->getData<int>("x"),
		newEntity->getData<int>("y"),
		newEntity->getData<int>("w"),
		newEntity->getData<int>("h")
	});
}