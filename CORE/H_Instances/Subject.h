#pragma once
#include "_Manager.h"
class Subject
{
public:
	virtual void execute() = 0;

	
};

class walkForwardButtonPressed : public Subject
{
	virtual void execute();
};

class walkBackwardButtonPressed : public Subject
{
	virtual void execute();
};

class walkLeftButtonPressed : public Subject
{
	virtual void execute();
};

class walkRightButtonPressed : public Subject
{
	virtual void execute();
};