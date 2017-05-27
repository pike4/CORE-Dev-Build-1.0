//#include "Spinner.h"
//#include "Manipulatable.h"
//#include "VideoManager.h"
//#include "ObjectManager.h"
//void Spinner::update()
//{
//	Manipulatable::rotate(rotationPerTick);
//}
//
//void Spinner::setRotationPerTick(double aRotationPerTick)
//{
//	rotationPerTick = aRotationPerTick;
//}
//
//
//Spinner::Spinner(int x, int y, SDL_Texture* aTexture, SDL_RendererFlip aFlip, double aRotation, SDL_Point aPoint, double aRotationPerTick)
//	: BaseObject(x, y), Manipulatable(aTexture, aFlip, aRotation, aPoint)
//{
//	rotationPerTick = aRotationPerTick;
//}
//
//Spinner::Spinner(int x, int y, SDL_Texture* aTexture, double aRotationPerTick)
//	: BaseObject(x, y), Manipulatable(aTexture)
//{
//	rotationPerTick = aRotationPerTick;
//}
//
//Spinner::Spinner(int x, int y, SDL_Texture* aTexture)
//	:BaseObject(x, y), Manipulatable(aTexture)
//{
//	this->rotationPerTick = 0;
//}
//
//Spinner::Spinner(pugi::xml_node node, std::vector<BaseObject*>* objectVec, std::vector<Drawable*>* drawVec, std::vector<Updatable*>* updateVec)
//	:BaseObject(node, objectVec), Manipulatable(node, drawVec), Updatable(updateVec)
//{
//	int rot;
//	char* rotString = (char*)node.child("rotation_speed").first_child().value();
//
//	try { rot = stoi(rotString); }
//	catch(exception)
//	{ rot = 0; }
//
//}
//
//int Spinner::getX()
//{
//	return x;
//}
//
//int Spinner::getY()
//{
//	return y;
//}