#pragma once
class DataBound
{
public:
	bool realTime;
	virtual void submit() = 0;
};