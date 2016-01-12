#include "Mobile.h"

void Mobile::move()
{
	x += xVel;
	y += yVel;
}

Mobile::Mobile(int x, int y, SDL_Texture* texture) : Visible(texture), BaseObject(x, y)
{

}
