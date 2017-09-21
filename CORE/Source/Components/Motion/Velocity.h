#pragma once
#include "Position.h"

class Velocity : public Position
{
public:
	Velocity();
	Velocity(pugi::xml_node node);
	Velocity(Velocity&);
	virtual Component* spawnCopy();
	virtual void move(int aX, int aY);
   virtual void get_data(DataSource* source);

	virtual void handle(Event e);

protected:
	DataImpl<double>* xVel;
	DataImpl<double>* yVel;

	int* direction;
};