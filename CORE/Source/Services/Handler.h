#pragma once
#include "Entity.h"
#include "CORE_TypeTraits.h"

class Handler : public Entity
{
public:
    virtual void getText(Node* node);
    virtual void handle(Event e);
protected:
    // Vector containing the names and types of data members to request when a new 
    std::vector<reflection> format;


    // Given an entity, add it or get data from it in order to handle it
    virtual void add(Entity* newEntity) = 0;

    // Check that the given Entity has the data of the names and types specified in format
    bool entityMatchesFormat(Entity* ent);
};