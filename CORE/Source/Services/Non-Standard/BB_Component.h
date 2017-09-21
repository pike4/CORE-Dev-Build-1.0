#pragma once
#include "BoundingBox.h"
#include "BoundingBoxAccepter.h"
#include "Component.h"

class BB_Component : public Component
{
public:
   BB_Component();
   virtual void handle(Event e);

   virtual void get_data(DataSource* source);

   BoundingBox* getBoundingBox();

   BoundingBox aaa;
};