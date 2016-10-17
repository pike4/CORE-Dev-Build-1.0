#include "I_DrawComponent.h"
#include "GameObject.h"
#include "VideoManager.h"

Component* I_DrawComponent::spawnCopy()
{
	return new I_DrawComponent(*this);
}

I_DrawComponent::I_DrawComponent(pugi::xml_node node)
{
	node = node.child("CompositeDrawable");
	if (strcmp(node.name(), ""))
	{
		drawable = new CompositeDrawable(node);
	}

	events = { drawStep, updateStep };
}

I_DrawComponent::I_DrawComponent(I_DrawComponent& other)
{
	x = NULL;
	y = NULL;

	drawable = (CompositeDrawable*) other.drawable->spawnCopy();

	events = { drawStep, updateStep };
}

void I_DrawComponent::assignPointers(GameObject* parent)
{
	x = (int*)parent->getPointer("x", sizeof(int));
	y = (int*)parent->getPointer("y", sizeof(int));
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
}