#pragma once
#include "Provider.h"

class Default : public Provider
{
public:
	Default(std::string newName, std::string newValue);

	virtual std::string getValue(pugi::xml_node node);

protected:
	std::string value;
	std::string name;
};
