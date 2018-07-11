#include "UnexpandedNode.h"
#include "DefaultNode.h"
#include "VariableGetter.h"
#include "Constant.h"

UnexpandedNode::UnexpandedNode(pugi::xml_node node, TemplateDef* temp)
{
    templateDef = temp;

    readNode(node);
}

void UnexpandedNode::readNode(pugi::xml_node curNode)
{
    name = curNode.name();
	mainValue = NULL;

    pugi::xml_attribute attr = curNode.first_attribute();


    // Get attributes
    while (attr.name() != "")
    {
        // Add a variable getter
        if (attr.value()[0] == '?')
        {
            attributes.push_back({ attr.name(), new VariableGetter(templateDef->getAddress(attr.value() + 1)) });
        }

        // Add a const
        else
        {
            attributes.push_back({ attr.name(), new Constant(attr.value()) });
        }

        attr = attr.next_attribute();
    }


    pugi::xml_node childNode = curNode.first_child();

	if (childNode.name() == "" && childNode.value() != "")
	{
		// Add a variable getter
		if (childNode.value()[0] == '?')
		{
			mainValue = new VariableGetter(templateDef->getAddress(childNode.value() + 1));
		}

		// Add a const
		else
		{
			mainValue =  new Constant(childNode.value());
		}
	}

	else
	{
		while (childNode.name() != "")
		{
			if (!strcmp(childNode.name(), "sources"))
			{
				childNode = childNode.next_sibling();
				continue;
			}

			children.push_back(UnexpandedNode(childNode, templateDef));
			childNode = childNode.next_sibling();
		}
	}
}

DefaultNode UnexpandedNode::expand(pugi::xml_node node)
{
	DefaultNode ret;

	ret.setName(name);

    for (int i = 0; i < attributes.size(); i++)
    {
        ret.addAttribute(attributes[i].first, attributes[i].second->getValue(node));
    }

    for (int i = 0; i < children.size(); i++)
    {
		DefaultNode child = children[i].expand(node);

        ret.addChild(child);
    }

	if (children.size() == 0 && mainValue)
	{
		ret.setValue(mainValue->getValue(node));
	}

    return ret;
}

UnexpandedNode::UnexpandedNode() {}