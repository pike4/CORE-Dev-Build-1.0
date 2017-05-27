//#include "Visible.h"
//#include "VideoManager.h"
//#include "SystemManager.h"
//#include "BaseObject.h"
//#include "Room.h"
//
//Visible::Visible()
//{
//	//empty constructor for GUI elements and drawables that shouldn't be grouped with the other game objects.
//}
//
//Visible::Visible(SDL_Texture* texture)
//{
//	this->mTexture = texture;
//
//	VideoManager::addVisible(this);
//}
//
////Only use when this object's child class is being managed by some other structure
//Visible::Visible(pugi::xml_node node)
//{
//	mTexture = SystemManager::assignTexture((char*)node.child("texture").first_child().value());
//}
//
////Used to programatically add an existing Visible to a room
//Visible::Visible(Room* room)
//{
//	room->drawVector->push_back(this);
//}
//
////Used to create a new Visible from an XML node. Should change to 
//Visible::Visible(pugi::xml_node node, Room* room)
//{
//	mTexture = SystemManager::assignTexture((char*)node.child("texture").first_child().value());
//
//	room->drawVector->push_back(this);
//}
//
//Visible::Visible(pugi::xml_node node, std::vector<Visible*>* drawVector)
//{
//	mTexture = SystemManager::assignTexture((char*)node.child("texture").first_child().value());
//
//	drawVector->push_back(this);
//}
//
//
//void Visible::draw(SDL_Renderer* renderer)
//{
//	VideoManager::applyTexture(getX(), getY(), renderer, mTexture);
//}
//
//Visible::~Visible()
//{
//	VideoManager::removeVisible(this);
//}