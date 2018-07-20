#include "Handler.h"
#include "CORE_Resources.h"

void Handler::getText(Node* node)
{
	// Get required format
    Node* formatChild = node->getChild("format");
    std::vector<Node*>* formatChildren = formatChild->getChildren();

    for (int i = 0; i < formatChildren->size(); i++)
    {
        Node* curNode = (*formatChildren)[i];

        CORE_TypeTraits::reflection curTrait;
        CORE_TypeTraits::parseReflectionTraits(curNode, &curTrait);

        format.push_back(curTrait);
    }

	// Get all traits
	formatChild = node->getChild("traits");

	if (formatChild)
	{
		formatChildren = formatChild->getChildren();

		for (int i = 0; i < formatChildren->size(); i++)
		{
			Node* curNode = (*formatChildren)[i];
			std::string traitName = curNode->getName();

			traits.push_back(traitName);
		}
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
	// Must be implemented
}

bool Handler::entityMatchesFormat(Entity* ent)
{
    bool matches = true;
	std::vector<CORE_TypeTraits::reflection> form = getFormat();

    for (int i = 0; i < form.size(); i++)
    {
        Data* curData = ent->getRawPtr(form[i].name);

        if ( !(curData && curData->getType() == form[i].primitiveType) )
        {
            matches = false;
            break;
        }
    }

    return matches;
}

bool Handler::entityHasAllTraits(Entity* ent)
{
	std::vector<std::string> reqdTraits = getTraits();

	for (int i = 0; i < reqdTraits.size(); i++)
	{
		if (!ent->getTrait(reqdTraits[i]))
		{
			return false;
		}
	}

	return true;
}

std::vector<std::string> Handler::getTraits()
{
	return traits;
}

std::vector< CORE_TypeTraits::reflection > Handler::getFormat()
{
	return format;
}