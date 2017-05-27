#pragma once

#pragma warning(disable : 4800)
#pragma warning(disable : 4804)

#include "CORE_TypeTraits.h"
#include "CORE_SystemIO.h"

//Data classes basically need to be componentized


class Data
{	
public:
	
	virtual CORE_TypeTraits::PrimitiveType getType() = 0;

protected:
	//template<typename T>
	//T get() = 0;

	//template<typename T>
	//void set(T) = 0;
};

template <typename T>
class Transform;

template<typename T>
class DataImpl : public Data
{
public:

	virtual CORE_TypeTraits::PrimitiveType getType()
	{
		return CORE_TypeTraits::typeOfT<T>();
	}

	DataImpl(int funcType = 1);

//CAREFUL! These methods are unsafe. Be sure the correct type is alway supplied when
//adding dependencies, because DataImpl has no way of checking at runtime
#pragma region Dependency Management
	virtual void addDependency(Data* other)
	{
		if (sourceCount >= maxSources)
		{
			maxSources *= 2;
			DataImpl<T>** newDest = (DataImpl<T>**)malloc(maxSources * sizeof(DataImpl<T>*));
			memcpy(newDest, data, sourceCount * sizeof(DataImpl<T>*));
		}

		
      if (CORE_TypeTraits::dataIsType<T>(other))
          data[sourceCount++] = (DataImpl<T>*) other;

      else
          CORE_SystemIO::error("Tried to add dependency of incompatible type. Underlying data is "
              + CORE_TypeTraits::getPrimitiveTypeName(typeOfT<T>()) + " but new dependency is "
              + CORE_TypeTraits::getPrimitiveTypeName(other->getType()));
	}

	virtual void remove(Data* other)
	{
		bool found = false;
		
		for (unsigned int i = 0; i < sourceCount; i++)
		{
			if (data[i] == other)
			{
				found = true;
				--sourceCount;
			}

			if (found)
			{
				data[i] = data[i + 1];
			}
		}
	}

	T value;
	DataImpl<T>** data;
#pragma endregion
#pragma region Operators
	virtual operator T()
	{
		return get();
	}
	virtual void operator =(T value)
	{
		set(value);
	}
	virtual T& operator*()
	{
		return value;
	}
	virtual T operator +(DataImpl& other)
	{
		T temp = other.get();
		return get() + temp;
	}
	virtual T operator -(DataImpl& other)
	{
		T temp = other.get();
		return get() - temp;
	}
	virtual T operator *(DataImpl& other)
	{
		T temp = other.get();
		return get() * temp;
	}
	virtual T operator /(DataImpl& other)
	{
		T temp = other.get();
		return get() / temp;
	}
	virtual void operator++()
	{
		T temp = get();
		temp++;
		set(temp);
	}
	virtual void operator--()
	{
		T temp = get();
		temp = temp - 1;
		set(temp);
	}

	T& operator +=(T other)
	{
		T temp = get();
		temp += other;
		set(temp);
		return temp;
	}

	T& operator -=(T other)
	{
		T temp = get();
		temp -= other;
		set(temp);
		return temp;
	}

#pragma endregion

protected:
	Transform<T>* transform;

	virtual T get() const;
	virtual void set(T newValue)
	{
		value = newValue;
	}

	unsigned short sourceCount = 0;
	unsigned short maxSources = 2;
};

#include "Transform.h"
#include "TR_Simple.h"
#include "TR_Sum.h"
#include "TR_Offset.h"
#include "TR_Average.h"

using namespace CORE_TypeTraits;

template <typename T>
T DataImpl<T>::get() const
{
	return transform->get(this, sourceCount);
}

template <typename T>
DataImpl<T>::DataImpl(int funcType = 1)
{
    if (funcType == TR_SIMPLE)
        data = NULL;

    else
        data = (DataImpl<T>**)malloc(maxSources * sizeof(Data*));

	switch (funcType)
	{
	case TR_SIMPLE:
		transform = new TR_Simple<T>();
		break;
	case TR_OFFSET:
		transform = new TR_Offset<T>();
		break;
	case TR_SUM:
		transform = new TR_Sum<T>();
		break;
	case TR_AVERAGE:
		transform = new TR_Average<T>();
		break;
	default:
		break;
	}
}

//template <typename T>
//T operator +=(T& arg1, const DataImpl<T>& data)
//{
//	T arg2 = data;
//
//	arg1 += arg2;
//	return arg1;
//}
//
//template <typename T>
//T operator -=(T& arg1, const DataImpl<T>& data)
//{
//	T arg2 = data;
//
//	arg1 -= arg2;
//	return arg1;
//}
//
//template <typename T>
//T operator +=(DataImpl<T>& arg1, T& data)
//{
//	T arg2 = data;
//
//	arg1 += arg2;
//	return arg1;
//}
//
//template <typename T>
//T operator -=(DataImpl<T>& arg1, T& data)
//{
//	T arg2 = data;
//
//	arg1 -= arg2;
//	return arg1;
//}