#include "Visible.h"
#include "VideoManager.h"
#include "BaseObject.h"

Visible::Visible(SDL_Texture* texture)
{
	this->mTexture = texture;

	VideoManager::addVisible(this);
}

void Visible::draw(SDL_Renderer* renderer)
{
	VideoManager::applyTexture(getX(), getY(), renderer, mTexture);
}

Visible::~Visible()
{
	VideoManager::removeVisible(this);
}