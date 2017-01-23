#pragma once
#include "Control.h"
#include "ImageElement.h"
#include "DataBound.h"
#include "pugixml.hpp"

class CheckBoxButton : public Control, public DataBound
{
public:
	CheckBoxButton(Definer* definer);

	ImageElement* heldImage_Current;
	ImageElement* hoverImage_Current;
	ImageElement* defaultImage_Current;

	SDL_Texture* heldImage_Checked;
	SDL_Texture* heldImage_Unchecked;
	SDL_Texture* hoverImage_Checked;
	SDL_Texture* hoverImage_Unchecked;
	SDL_Texture* defaultImage_Checked;
	SDL_Texture* defaultImage_Unchecked;

	virtual void handleInput(int keyCode, int upDown = 0, int x = 0, int y = 0);

protected:
	bool* dataBinding;
	bool checked;

	virtual void mouseEnter();
	virtual void mouseLeave();
	virtual void mouseDown();
	virtual void mouseUp();

	void check();
	void uncheck();

	virtual void submit();
};