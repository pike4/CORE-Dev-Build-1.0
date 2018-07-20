#include "Event.h"
#include "CORE_Resources.h"

void Event::pushEntity(Entity* e)
{
   arguments.push_back(e);
}

Event::Event(int code)
{
   opcode = code;
}

Event::Event(std::string name) :
   Event(CORE_Resources::getEventCode(name))
{
}

Event::Event(int code, std::vector<EventArg> args) :
   Event(code)
{
   arguments = args;
}

Event::Event(std::string name, std::vector<EventArg> args) :
   Event(CORE_Resources::getEventCode(name), args) {}