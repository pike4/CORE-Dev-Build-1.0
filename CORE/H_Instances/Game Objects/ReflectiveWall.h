#include "Collidable.h"
#include "Thing.h"
#include "SDL.h"

class ReflectiveWall : public Collidable, public Visible, public BaseObject
{
public:
	ReflectiveWall(int aX, int aY, int aW, int aH,  SDL_Texture* mTexture);


};