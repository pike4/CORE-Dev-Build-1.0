#pragma once

class Data
{
public:
	
protected:
	template<typename T>
	T get() = 0;

	template<typename T>
	void set(T other) = 0;
};

template<typename T>
class DataImpl : public Data
{
public:
	DataImpl()
	{
		data = new T;
	}

	virtual operator T&()
	{
		return get();
	}

	virtual void operator =(T value)
	{
		set(value);
	}

	virtual T operator +(DataImpl& other)
	{
		return *data + *(other.data);
	}
	virtual T operator -(DataImpl& other)
	{
		return *data - *(other.data);
	}
	virtual T operator *(DataImpl& other)
	{
		return *data * *(other.data);
	}
	virtual T operator /(DataImpl& other)
	{
		return *data + *(other.data);
	}

	//virtual void operator +=(T value)
	//{
	//	*data += value;
	//	set(value);
	//}

	//virtual void operator -=(T value)
	//{
	//	*data -= value;
	//	set(value);
	//}

	virtual void operator++()
	{
		*data++;
	}

	virtual void operator--()
	{
		*data--;
	}


protected:
	T* data;
	virtual void set(T value) = 0;
	virtual T& get() const = 0;
};

template <typename T>
T& operator +=(T& arg1, const DataImpl<T>& data)
{
	T arg2 = data;

	arg1 += arg2;
	return arg1;
}

//template <typename T>
//T& operator -=(T& arg1, const DataImpl<T>& data)
//{
//	T arg2 = data;
//
//	arg1 -= arg2;
//	return arg1;
//}

//template <typename S, typename T>
//S& operator +=(DataImpl<S>& arg1, const DataImpl<T>& data)
//{
//	T arg2 = data;
//	arg1 += arg2;
//	return arg1;
//}


template<typename T>
class Dependency : public DataImpl<T>
{
public:
	Dependency() : DataImpl()
	{
		sources = (DataImpl<T>**)malloc(maxSources * sizeof(Data*));
	}

	virtual void addDependency(DataImpl<T>* other)
	{
		if (sourceCount >= maxSources)
		{
			maxSources *= 2;
			Data** newDest = (Data**) malloc(maxSources * sizeof(Data*));
			memcpy(newDest, sources, sourceCount * sizeof(Data*));
		}

		sources[sourceCount++] = other;
	}

	virtual void remove(DataImpl<T>* other)
	{
		bool found = false;

		for (unsigned int i = 0; i < sourceCount; i++)
		{
			if (sources[i] == other)
			{
				found = true;
				--sourceCount;
			}

			if (found)
			{
				sources[i] = sources[i + 1];
			}
		}
	}
protected:
	short sourceCount = 0;
	short maxSources = 2;
	DataImpl<T>** sources;
};

template<typename T>
class SimpleData : public DataImpl<T>
{
public:

	SimpleData() : DataImpl() {}
	SimpleData(T value) : DataImpl() { set(value);}

	virtual void operator =(T value)
	{
		set(value);
	}

	virtual operator T&()
	{
		return get();
	}

	virtual void set(T value)
	{
		*data = value;
	}

	virtual T& operator *()
	{
		return get();
	}

	virtual T& get() const
	{
		return *data;
	}

	virtual void addDependency(Data* other)
	{
		//exception, can't add dependency to this type
	}

	virtual void remove(Data* other)
	{
		//exception, this type has no dependencies
	}
};

template<typename T>
class DataSum : public Dependency<T>
{
public:
	DataSum() : Dependency() {}

	DataSum(T value)
	{
		set(value);
	}

	virtual void operator =(T value)
	{
		set(value);
	}

	virtual T& operator *()
	{
		return get();
	}

	virtual operator T&()
	{
		return get();
	}

protected:

	virtual void set(T val) {}//warning: dataSum cannot be set this way
	
	//Return the sum of all dependencies
	virtual T get() const
	{
		T ret = 0;

		for (unsigned int i = 0; i < sourceCount; i++)
		{
			Data* source = sources[i];
			ret += *source;
		}

		return ret;
	}
};

template<typename T>
class DataOffset : public Dependency<T>
{
public:
	DataOffset() : Dependency() {}
	DataOffset(T value)
	{
		set(value);
	}

	virtual void operator =(T value)
	{
		set(value);
	}

	virtual T& operator *()
	{
		return get();
	}

	virtual operator T&()
	{
		return get();
	}

protected:
	
	//Set the offset value
	virtual void set(T value)
	{
		offset = value;
	}

	//Offset plus sum of all dependencies
	virtual T& get() const
	{
		T ret = offset;

		for (unsigned int i = 0; i < sourceCount; i++)
		{
			T temp = *sources[i];
			ret += temp;
		}

		return ret;
	}

	T offset;
};

template<typename T>
class DataAverage : public Dependency<T>
{
public:
	DataAverage() : Dependency() {}

	DataAverage(T value)
	{
		set(value);
	}

	virtual void operator =(T value)
	{
		set(value);
	}

protected:

	//Set the offset value
	virtual void set(T value)
	{
		offset = value;
	}

	//Offset plus sum of all dependencies
	virtual T get() const
	{
		T ret = offset;

		for (unsigned int i = 0; i < sourceCount; i++)
		{
			ret += *sources[i];
		}

		return ret / sourceCount;
	}
};