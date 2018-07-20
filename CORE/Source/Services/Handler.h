#pragma once
#include "Entity.h"
#include "CORE_TypeTraits.h"

class Handler : public Entity
{
public:
    virtual void getText(DefaultNode* node);
    virtual void handle(Event e);
protected:
    // Vector containing the names and types of data members to request when a new 
    std::vector<reflection> format;

	// Vector containing names of traits required by this handler
	std::vector<std::string> traits;

    // Given an entity, add it or get data from it in order to handle it
    virtual void add(Entity* newEntity);

    // Check that the given Entity has the data of the names and types specified in format
    bool entityMatchesFormat(Entity* ent);

	// Check that the given entity has all of the traits needed by this handler
	bool entityHasAllTraits(Entity* ent);

	// Get the list of traits this Handler requires
	virtual std::vector<std::string> getTraits();

	// Get the format this Handler requires
	virtual std::vector< CORE_TypeTraits::reflection > getFormat();
};