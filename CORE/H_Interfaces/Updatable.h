#pragma once
#include <vector>

class Updatable
{
public:
	virtual void update() = 0;
	Updatable();
	Updatable(std::vector<Updatable*>*);
	~Updatable();
};