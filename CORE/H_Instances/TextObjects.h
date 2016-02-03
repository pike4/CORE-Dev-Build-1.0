#include "Visible.h"
#include "BaseObject.h"
#include "SDL_ttf.h"
#include "Thing.h"

class PlainText : public Thing
{
public:
	PlainText(int x, int y, TTF_Font* aFont, char* aText, SDL_Color fg);

	int getX();
	int getY();

private:
	TTF_Font* font;

};