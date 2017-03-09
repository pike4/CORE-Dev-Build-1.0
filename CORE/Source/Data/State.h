#pragma once
#include <map>
#include "Data.h"
#include "StateOffsetCalculator.h"
#include "CORE_SystemIO.h"

class State
{
public:
    template <typename T>
    DataImpl<T>* getData(std::string name)
    {
        DataImpl<T>* ret = NULL;

        if (publicData.find(name) != publicData.end())
        {
            ret = publicData[name];
        }

        else
        {
            std::string requestedType = CORE_TypeTraits::getPrimitiveTypeName(foundData->getType());
            std::string foundType = CORE_TypeTraits::getPrimitiveTypeName(CORE_TypeTraits::typeOfT<T>);

            CORE_SystemIO::error("Client expected Data " + name + " of type " + requestedType
                + " but data is " + foundType);
        }

        return ret;
    }

    template <typename T>
    void addVariable(std::string name, T initialValue = 0)
    {
        if (!variableExists(name))
        {
            DataImpl<T>* newData = new DataImpl<T>();
            *newData = initialValue;
            publicData[name] = newData;
        }

        else
        {
            CORE_SystemIO::error("Variable " + name + " already exists");
        }
    }

    void addData(std::string name, Data* newData);

    template <typename T>
    void setValue(std::string name, T value)
    {
        if (variableExists(name))
        {
           if (CORE_TypeTraits::dataIsType<T>(publicData[name]))
           {
              *((DataImpl<T>*) publicData[name]) = value;
           }
        }

        else
        {
            CORE_SystemIO::error("Variable " + name + " does not exist");
        }
    }

    template <typename T>
    T getValue(std::string name)
    {
        T ret = 0;
        DataImpl<T>* dat = NULL;

        if (publicData.find(name) != publicData.end())
        {
            Data* foundData = publicData[name];

            //Check if data found is of the same type as was requested
            if (dataIsType<T>(foundData))
            {
                dat = (DataImpl<T>*) foundData;
                ret = *dat;
            }

            else
            {
                std::string requestedType = CORE_TypeTraits::getPrimitiveTypeName(foundData->getType());
                std::string foundType = CORE_TypeTraits::getPrimitiveTypeName
                (CORE_TypeTraits::typeOfT<T>());

                CORE_SystemIO::error("Client expected Data " + name + " of type " + requestedType
                    + " but data is " + foundType);
            }
        }

        else
        {
            CORE_SystemIO::error("Variable " + name + " not found");
        }

        return ret;
    }

    //True if this contains a variable of the given name and type
    template <typename T>
    bool variableOfTypeExists(std::string name)
    {
        return (variableExists(name) && dataIsType<T>(publicData[name]));
    }

    //True if this contains a variable of the given name
    bool variableExists(std::string name)
    {
        return (publicData.find(name) != publicData.end());
    }

private:
    std::map<std::string, Data*> publicData;
};


// "Better" Implementation that doesn't rely on everything storing its own map. All improvements are 
//performance related. Wait until engine is in Alpha to implement
//class State
//{
//public:
//
//    template <typename T>
//    DataImpl<T>* getData(std::string name)
//    {
//        DataImpl<T>* ret = NULL;
//        int offset = offsetCalculator->getOffset(name);
//
//        if (offset != -1)
//        {
//            Data* foundData = (char*) data + offset;
//
//            //Check if data found is of the same type as was requested
//            if (dataIsType<T>(foundData))
//            {
//                ret = (DataImpl<T>*) foundData;
//            }
//
//            else
//            {
//                std::string requestedType = CORE_TypeTraits::getPrimitiveTypeName(foundData->getType());
//                std::string foundType = CORE_TypeTraits::getPrimitiveTypeName(CORE_TypeTraits::typeOfT<T>);
//
//                CORE_SystemIO::error("Client expected Data " + name + " of type " + requestedType
//                    + " but data is " + foundType);
//            }
//        }
//
//        return ret;
//    }
//
//    template <typename T>
//    void setValue(std::string name, T value)
//    {
//        DataImpl<T>* dat = NULL;
//        int offset = offsetCalculator->getOffset(name);
//
//        if (offset != -1)
//        {
//            Data* foundData = (char*)data + offset;
//
//            //Check if data found is of the same type as was requested
//            if (dataIsType<T>(foundData))
//            {
//                dat = (DataImpl<T>*) foundData;
//                *dat = value;
//            }
//
//            else
//            {
//                std::string requestedType = CORE_TypeTraits::getPrimitiveTypeName(foundData->getType());
//                std::string foundType = CORE_TypeTraits::getPrimitiveTypeName(CORE_TypeTraits::typeOfT<T>);
//
//                CORE_SystemIO::error("Client expected Data " + name + " of type " + requestedType
//                    + " but data is " + foundType);
//            }
//        }
//    }
//
//    template <typename T>
//    T getValue(std::string name)
//    {
//        T ret = 0;
//        DataImpl<T>* dat = NULL;
//        int offset = offsetCalculator->getOffset(name);
//
//        if (offset != -1)
//        {
//            Data* foundData = (char*)data + offset;
//
//            //Check if data found is of the same type as was requested
//            if (dataIsType<T>(foundData))
//            {
//                dat = (DataImpl<T>*) foundData;
//                ret = *dat;
//            }
//
//            else
//            {
//                std::string requestedType = CORE_TypeTraits::getPrimitiveTypeName(foundData->getType());
//                std::string foundType = CORE_TypeTraits::getPrimitiveTypeName
//                    (CORE_TypeTraits::typeOfT<T>);
//
//                CORE_SystemIO::error("Client expected Data " + name + " of type " + requestedType
//                    + " but data is " + foundType);
//            }
//        }
//
//        return ret;
//    }
//
//    //True if this contains a variable of the given name
//    bool variableExists(std::string name)
//    {
//        return (offsetCalculator->getOffset(name) != -1);
//    }
//
//    //True if this contains a variable of the given name and type
//    template <typename T>
//    bool variableOfTypeExists(std::string name)
//    {
//        int offset = offsetCalculator->getOffset(name);
//        Data* foundData = NULL;
//
//        if (offset != -1)
//            foundData = (char*)data + offset;
//
//        return (offset != -1 && foundData && dataIsType<T>(foundData));
//    }
//
//
//    //Implement this if needed, but I doubt it ever will be
//    //Add a variable of the given name and type and secure a new offsetCalculator if necessary
//    //template <typename T>
//    //void addVariable(std::string name, T initialValue = 0)
//    //{
//    //    if (offsetCalculator && variableExists(name))
//    //    {
//    //        CORE_SystemIO::error("Could not add variable, the state already contains variable " + name);
//    //        return;
//    //    }
//    //        
//    //    int size = CORE_TypeTraits::sizeOfT<T>();
//    //    std::vector<std::string> curOffsetCalc;
//    //    if(offsetCalculator)
//    //        curOffsetCalc = offsetCalculator->getFingerprint();
//    //
//    //    curOffsetCalc.push_back(name);
//    //    curOffsetCalc.push_back(CORE_TypeTraits::getPrimitiveTypeName(CORE_TypeTraits::typeOfT<T>()));
//    //    //Get a new offset calculator according to the new variable
//    //    offsetCalculator = CORE_Resources::getStateOffsetCalculator(curOffsetCalc);
//    //
//    //    //Move data to new position
//    //    for (std::map<std::string, int>::iterator it = offsetCalculator->offsets.begin(); 
//    //        it != offsetCalculator->offsets.end(); ++it)
//    //    {
//    //        std::string curVal = it->first;
//    //        void 
//    //
//    //    }
//    //}
//
//private:
//    void* data;     //Pointer to contiguous array of Data *objects* not pointers
//    short size;     //Data array size
//    short count;    //Number of Data objects in this State
//
//    //Used to determine where each Data object is located relative to the data pointer
//    StateOffsetCalculator* offsetCalculator;
//};