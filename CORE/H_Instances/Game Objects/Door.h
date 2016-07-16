#pragma once
#include "TriggerZone.h"

class Door : public TriggerZone, public Visible
{
public:
	std::string pointer;

	Door(pugi::xml_node, std::vector<BaseObject*>* objectVector, std::vector<Visible*>* drawVector, std::vector<Collidable*>* collidableVector);

	void onCollide(Player* p);
	void onCollide(BouncingBall* b);
	void onCollide(Cursor* c);
	void onCollide(Door* d);

	int getX();
	int getY();
};