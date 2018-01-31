#include "Handler.h"
#include "CORE_Resources.h"

void Handler::getText(Node* node)
{
    Node* formatChild = node->getChild("format");
    std::vector<Node*>* formatChildren = formatChild->getChildren();

    for (int i = 0; i < formatChildren->size(); i++)
    {
        Node* curNode = (*formatChildren)[i];

        CORE_TypeTraits::reflection curTrait;
        CORE_TypeTraits::parseReflectionTraits(curNode, &curTrait);

        format.push_back(curTrait);
    }

	formatChild = node->getChild("traits");
	formatChildren = formatChild->getChildren();

	for (int i = 0; i < formatChildren->size(); i++)
	{
		Node* curNode = (*formatChildren)[i];
		std::string traitName = curNode->getName();

		requiredTraits.push_back(traitName);
	}
}

void Handler::handle(Event e)
{
    // Double check that the given argument is an entity, then add it for handling
    if (e.opcode == entity_added && e.arguments.size() > 0 && e.arguments[0].entity != NULL )
    {
        Entity* newEnt = e.arguments[0].entity;

        if (entityMatchesFormat(newEnt))
        {
            add(newEnt);
        }
    }
}

void Handler::add(Entity* e)
{

}

bool Handler::entityMatchesFormat(Entity* ent)
{
    bool matches = true;

    for (int i = 0; i < format.size(); i++)
    {
        Data* curData = ent->getRawPtr(format[i].name);

        if ( !(curData && curData->getType() == format[i].primitiveType) )
        {
            matches = false;
            break;
        }
    }

    return matches;
}

bool Handler::entityHasAllTraits(Entity* ent)
{
	for (int i = 0; i < requiredTraits.size(); i++)
	{
		if (!ent->getTrait(requiredTraits[i]))
		{
			return false;
		}
	}

	return true;
}