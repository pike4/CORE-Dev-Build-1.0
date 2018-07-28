#include "CORE_Resources.h"
#include "StandardCollision.h"
#include "CORE.h"

void StandardCollision::handle(Event e)
{
	Handler::handle(e);

	switch (e.opcode)
	{
	case updateStep:
		for (unsigned int i = 0; i < boundingBoxes.size(); i++)
		{
			for (unsigned int j = i; j < boundingBoxes.size(); j++)
			{
				if (i == j) continue;

				BoundingBox a = boundingBoxes[i];
				BoundingBox b = boundingBoxes[j];

				if (*a.x + *a.w > *b.x
					&& *a.x < *b.x + *b.w
					&& *a.y < *b.y + *b.h
					&& *a.y + *a.h > *b.y)
				{
					Event e(collision);
					e.pushEntity(a.e);
					e.pushEntity(b.e);

					CORE::handle(e);
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
		newEntity,
		newEntity->getData<int>("x"),
		newEntity->getData<int>("y"),
		newEntity->getData<int>("w"),
		newEntity->getData<int>("h")
	});
}