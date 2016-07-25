#include "ImageElement.h"
#include "VideoManager.h"
#include "SystemManager.h"

ImageElement::ImageElement(int x, int y, int w, int h, SDL_Texture* texture)
	:VisibleElement(x, y, w, h)
{
	this->texture = texture;


}

ImageElement::ImageElement(pugi::xml_node node)
	:VisibleElement(node)
{
	texture = SystemManager::assignTexture(node.child("Image").first_child().value());
}

ImageElement::ImageElement(ImageElement& copy)
	:VisibleElement(copy)
{
	texture = copy.texture;
}

void ImageElement::draw(SDL_Renderer* renderer)
{
	VideoManager::applyTexture(box.x, box.y, renderer, texture);
}

void ImageElement::getArgsFromNode(pugi::xml_node node)
{
	std::string textureName = node.child("Texture").first_child().value();
	if (!textureName.empty())
	{
		texture = SystemManager::assignTexture(textureName);
	}
	
	if (texture == NULL)
	{
		//TODO: log error
	}
}