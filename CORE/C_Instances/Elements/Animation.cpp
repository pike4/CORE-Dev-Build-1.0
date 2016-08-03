#include "Animation.h"
#include "VideoManager.h"

Animation::Animation(pugi::xml_node node)
 : VisibleElement(node)
{
	std::string fileName = node.child("fileName").first_child().value();
	millisecondsPerFrame = atoi(node.child("millisecondsPerFrame").first_child().value());
	int frameH = atoi(node.child("frameH").first_child().value());
	int frameW = atoi(node.child("frameW").first_child().value());
	int framesX = atoi(node.child("framesX").first_child().value());
	int framesY = atoi(node.child("framesY").first_child().value());
	int seperation = atoi(node.child("seperation").first_child().value());

	frames = new VisibleElement*[framesX * framesY];

	numFrames = framesX * framesY;
	
	VideoManager::getAnimationFromSpriteSheet(framesX, framesY, frameW, frameH, seperation, fileName, frames);
}

void Animation::draw(SDL_Renderer* renderer)
{
	if (frameTimer.hasElapsed(millisecondsPerFrame))
	{
		if (++frameIndex >= numFrames)
		{
			frameIndex = 0;
		}

		frameTimer.updateTime();
	}

	frames[frameIndex]->draw(renderer);
}

void Animation::move(int x, int y)
{
	for (int i = 0; i < numFrames; i++)
	{
		frames[i]->move(x, y);
	}
}