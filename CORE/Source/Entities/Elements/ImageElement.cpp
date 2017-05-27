#include "ImageElement.h"
#include "CORE_Graphics.h"
#include "CORE_Resources.h"

ImageElement::ImageElement() {}

ImageElement::ImageElement(int x, int y, int w, int h, SDL_Texture* texture)
	:VisibleElement(x, y, w, h)
{
	this->texture = texture;
}

void ImageElement::getText(Node* definer)
{
	VisibleElement::getText(definer);
	texture = CORE_Resources::assignTexture(definer->getVariable("image"));
}

ImageElement::ImageElement(ImageElement& copy)
	:VisibleElement(copy)
{
	ImageElement* t = this;
	texture = copy.texture;
}

void ImageElement::draw()
{
	CORE_Graphics::addDraw( *x, *y, texture , *zIndex);
}

void ImageElement::getArgsFromNode(Node* definer)
{
	std::string textureName = definer->getVariable("texture");
	if (!textureName.empty())
	{
		texture = CORE_Resources::assignTexture(textureName);
	}
	
	if (texture == NULL)
	{
		//TODO: log error
	}
}

Component* ImageElement::spawnCopy()
{
	ImageElement* blargle = new ImageElement(*this);
	return blargle;
}

void ImageElement::handleInput(int key, int upDown, int x, int y)
{
	switch (key)
	{
	case drawStep:
		draw();
		break;

	default:

		break;
	}
}