#pragma once
#include "Definer.h"
#include "Provider.h"
#include "Default.h"
#include "NodeValue.h"
#include "NodeMain.h"
#include "Variable.h"
#include "Constant.h"

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "pugixml.hpp"

class TemplateDef
{
public:
	TemplateDef(Definer* def);
	std::string getVariable(pugi::xml_node node, std::string name);
	
	//Name used to refer to this template
	std::string name;

	//Name of the type that this template is used to stand for
	std::string surname;

protected:
	std::map<std::string, Provider*> variables;
};