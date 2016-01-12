#include "Visible.h"
#include "VideoManager.h"
#include "BaseObject.h"

Visible::Visible(SDL_Texture* texture)
{
	this->mTexture = texture;

	VideoManager::addVisible(this);
}