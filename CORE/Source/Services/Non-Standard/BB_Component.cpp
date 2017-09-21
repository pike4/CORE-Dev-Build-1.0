#include "BB_Component.h"
#include "CORE_Resources.h"

BB_Component::BB_Component()
{
   events.push_back( CORE_Resources::getEventCode("getBoundingBox") );
}

void BB_Component::handle(Event e)
{
   const int getBBEvent = CORE_Resources::getEventCode("getBoundingBox");
   
   if (e.opcode == getBBEvent)
   {
      (dynamic_cast<BoundingBoxAccepter*>(e.arguments[0].entity))->accept(getBoundingBox());
   }
}

BoundingBox* BB_Component::getBoundingBox()
{
   return &aaa;
}

void BB_Component::get_data(DataSource* source)
{
   aaa.x = source->getData<int>("x");
   aaa.y = source->getData<int>("y");
   aaa.w = source->getData<int>("w");
   aaa.h = source->getData<int>("h");
}