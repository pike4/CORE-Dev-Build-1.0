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

    while (childNode.name() != "")
    {
        if (childNode.name() == "sources")
        {
            childNode = childNode.next_sibling();
            continue;
        }

        children.push_back(UnexpandedNode(childNode, templateDef));
        childNode = childNode.next_sibling();
    }
}

pugi::xml_node UnexpandedNode::expand(pugi::xml_node node)
{
    pugi::xml_node ret;

    for (int i = 0; i < attributes.size(); i++)
    {
        ret.append_attribute(attributes[i].first.c_str()) = attributes[i].second->getValue(node).c_str();
    }

    for (int i = 0; i < children.size(); i++)
    {
        pugi::xml_node child = children[i].expand(node);

        ret.append_child(child.name());
        ret.child(child.name()) = child;
    }

    return ret;
}

UnexpandedNode::UnexpandedNode() {}