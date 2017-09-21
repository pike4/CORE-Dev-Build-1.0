#pragma once
#include "Data.h"
#include <vector>

class Entity;

struct EventArg
{
   Entity* entity;
   Data* data;

   EventArg() {}
   EventArg(Entity* en)
   {
      entity = en;
      data = NULL;
   }

   EventArg(Data* d)
   {
      data = d;
      entity = NULL;
   }
};

struct Event
{
   int opcode;
   std::vector<EventArg> arguments;
  // std::vector<Data*> deleteList;

   template<typename T>
   void push(T newData)
   {
      DataImpl<T>* dat = new DataImpl<T>(TR_SIMPLE);
      *dat = newData;
      arguments.push_back(dat);
      //deleteList.push_back(dat);
   }

   void pushEntity(Entity* e);

   Event(int code);

   Event(std::string name);

   Event(int code, std::vector<EventArg> args);

   Event(std::string name, std::vector<EventArg> args);

   ~Event() {
      this;
      arguments.clear();
   }
};