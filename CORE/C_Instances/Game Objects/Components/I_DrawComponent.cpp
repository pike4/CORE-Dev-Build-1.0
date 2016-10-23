#include "I_DrawComponent.h"
#include "Entity.h"
#include "VideoManager.h"

/*I_DrawComponent::I_DrawComponent()
{
	pointers.push_back({ "x", sizeof(int), &x });
	pointers.push_back({ "y", sizeof(int), &y });
}

Component* I_DrawComponent::spawnCopy()
{
	return new I_DrawComponent(*this);
}

I_DrawComponent::I_DrawComponent(pugi::xml_node node)
	:I_DrawComponent()
{
	node = node.child("CompositeDrawable");
	if (strcmp(node.name(), ""))
	{
		drawable = new CompositeDrawable(node);
	}

	events = { drawStep, updateStep };
}

I_DrawComponent::I_DrawComponent(I_DrawComponent& other)
	:I_DrawComponent()
{
	x = NULL;
	y = NULL;

	drawable = (CompositeDrawable*) other.drawable->spawnCopy();
	events = { drawStep, updateStep };
}

void I_DrawComponent::handleInput(int key, int upDown, int mX, int mY)
{
	switch (key)
	{
	case drawStep:
		drawable->draw(VideoManager::mRenderer);
		break;
	case updateStep:
		drawable->handleInput(updateStep);
		drawable->move(*x, *y);
		break;
	}
}*/