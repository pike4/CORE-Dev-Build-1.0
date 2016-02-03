#pragma once
#include "_Manager.h"
class Subject
{
public:
	virtual void execute(int type) = 0;

	
};

class walkForwardButtonPressed : public Subject
{
	virtual void execute(int type);
};

class walkBackwardButtonPressed : public Subject
{
	virtual void execute(int type);
};

class walkLeftButtonPressed : public Subject
{
	virtual void execute(int type);
};

class walkRightButtonPressed : public Subject
{
	virtual void execute(int type);
};
