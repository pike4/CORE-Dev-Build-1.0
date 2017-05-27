#pragma once
#include "Provider.h"

class Constant : public Provider
{
public:
	Constant(std::string newValue);
	virtual std::string getValue(pugi::xml_node node);

protected:
	std::string value;
};