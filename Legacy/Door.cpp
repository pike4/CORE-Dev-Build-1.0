//#include "Door.h"
//#include "StateManager.h"
//
//Door::Door(pugi::xml_node node, std::vector<BaseObject*>* objectVector, std::vector<Visible*>* drawVector, std::vector<Collidable*>* collidableVector)
//	:TriggerZone(node, objectVector, collidableVector), Visible(node, drawVector)
//{
//	pointer = node.child("pointer").first_child().value();
//
//	prevXPtr = &x;
//	prevYPtr = &y;
//
//	collidableType = cDoor;
//}
//
//void Door::onCollide(Player* p)
//{
//	StateManager::goToRoomInCurrentEnvironment(pointer);
//}
//
//void Door::onCollide(BouncingBall* b)
//{
//
//}
//
//void Door::onCollide(Cursor* c)
//{
//
//}
//
//void Door::onCollide(Door* d) {}
//
//int Door::getX()
//{
//	return x;
//}
//
//int Door::getY()
//{
//	return y;
//}