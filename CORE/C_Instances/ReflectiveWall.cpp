#include "ReflectiveWall.h"

ReflectiveWall::ReflectiveWall(int aX, int aY, int aW, int aH,  SDL_Texture* mTexture)
	:BaseObject(aX, aY), Visible(mTexture), Collidable(aX, aY, aW, aH)
{

}