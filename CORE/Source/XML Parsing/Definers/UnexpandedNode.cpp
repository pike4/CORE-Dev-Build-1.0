#include "UnexpandedNode.h"
#include "VariableGetter.h"
#include "Constant.h"

UnexpandedNode::UnexpandedNode(pugi::xml_node node)
{
	name = node.name();

	pugi::xml_attribute attr = node.first_attribute();


	// Get attributes
	while (attr.name() != "")
	{
		// Add a variable getter
		if (attr.value()[0] == '?')
		{
			attributes.push_back({ attr.name(), new VariableGetter() });
		}

		// Add a const
		else
		{
			attributes.push_back({ attr.name(), new Constant(attr.value()) });
		}
	}

	// Get children TODO
}