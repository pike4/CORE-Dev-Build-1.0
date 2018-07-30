#include "CORE_Resources.h"
#include "StandardCollision.h"
#include "CORE.h"

StandardCollision::StandardCollision() : Handler()
{
	events.push_back(entity_added);
}

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
					Event e(collision);
					e.pushEntity(a.e);
					e.pushEntity(b.e);
					
					CORE::receive(e);

					Event e2(selfCollision);
					e2.pushEntity(a.e);
					CORE::direct(e2, b.e);

					Event e3(selfCollision);
					e3.pushEntity(b.e);
					CORE::direct(e3, a.e);
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