#include "ImageElement.h"
#include "VideoManager.h"

ImageElement::ImageElement(int x, int y, int w, int h, SDL_Texture* texture)
	:VisibleElement(x, y, w, h)
{
	this->texture = texture;


}

ImageElement::ImageElement(pugi::xml_node node)
	:VisibleElement(node)
{

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