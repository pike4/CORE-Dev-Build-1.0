//#include "Visible.h"
//#include "Manipulatable.h"
//#include "VideoManager.h"
//
//void Manipulatable::draw(SDL_Renderer* mRenderer)
//{
//	VideoManager::applyTexture(getX(), getY(), mRenderer, mTexture, rotation, flip, point);
//}
//
////Rotate the image to the specified absolute rotation
//void Manipulatable::setRotation(double aRotation)
//{
//	rotation = aRotation;
//}
//
////Rotate the image by the specified amount relative to current rotation
//void Manipulatable::rotate(double aRotation)
//{
//	rotation += aRotation;
//}
//
////New Manipulatable at given flip and rotation
//Manipulatable::Manipulatable(SDL_Texture* texture, SDL_RendererFlip aFlip, double aRotation, SDL_Point aPoint)
//	:Visible(texture)
//{
//	flip = aFlip;
//	rotation = aRotation;
//	point = aPoint;
//}
//
//Manipulatable::Manipulatable(pugi::xml_node node, std::vector<Visible*>* drawVector) : Visible(node, drawVector)
//{
//	int rot, pointX, pointY;
//	char* string_Rot = (char*)node.child("rotation").first_child().value();
//	char* string_pointX = (char*)node.child("pointX").first_child().value();
//	char* string_pointY = (char*)node.child("pointY").first_child().value();
//
//	try
//	{ rot = stoi(string_Rot); }
//
//	catch (exception)
//	{rot = 0;}
//
//	try
//	{ pointX = stoi(string_pointX); }
//
//	catch(exception)
//	{pointY = stoi(string_pointY);}
//}
//
////New Manipulatable at default flip and rotation
//Manipulatable::Manipulatable(SDL_Texture* texture) : Visible(texture)
//{
//	flip = SDL_FLIP_NONE;
//	rotation = 0;
//	SDL_Point lPoint;
//	int x, y;
//	SDL_QueryTexture(texture, NULL, NULL, &x, &y);
//
//	lPoint.x = x/2;
//	lPoint.y = y/2;
//
//	point = lPoint;
//}