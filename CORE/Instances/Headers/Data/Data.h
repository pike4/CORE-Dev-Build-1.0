#pragma once

class GenericData
{

};

template<typename T>
class Data : GenericData
{
public:
	Data()
	{
		data = new T;
	}

	virtual void operator =(T value)
	{
		set(value);
	}

	void operator +=(T value)
	{
		T initial = get();
		initial += value;
		set(T);
	}

	void operator -=(T value)
	{
		T initial = get();
		initial -= value;
		set(T);
	}

	operator const T&() const
	{
		return get();
	}

	

protected:
	T* data;
	virtual void set(T value) = 0;
	virtual T get() const = 0;
	virtual void add(Data* other) = 0;
	virtual void remove(Data* other) = 0;
};

template<typename T>
class Dependency : public Data<T>
{
public:
	Dependency() : Data()
	{
		sources = (Data**)malloc(maxSources * sizeof(Data*));
	}

	virtual void add(Data* other)
	{
		if (sourceCount >= maxSources)
		{
			maxSources *= 2;
			Data** newDest = (Data**) malloc(maxSources * sizeof(Data*));
			memcpy(newDest, sources, sourceCount * sizeof(Data*));
		}

		sources[sourceCount++] = other;
	}

	virtual void remove(Data* other)
	{
		bool found = false;

		for (int i = 0; i < sourceCount; i++)
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
	Data** sources;
};

template<typename T>
class SimpleData : public Data<T>
{
public:

	SimpleData() : Data() {}
	SimpleData(T value) : Data() { set(value);}

	virtual void operator =(T value)
	{
		set(value);
	}

	virtual void set(T value)
	{
		*data = value;
	}

	virtual T get() const
	{
		return *data;
	}

	virtual void add(Data* other)
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
protected:

	virtual void set(T val) {}//warning: dataSum cannot be set this way
	
	//Return the sum of all dependencies
	virtual T get() const
	{
		T ret = 0;

		for (int i = 0; i < sourceCount; i++)
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

		for (int i = 0; i < sourceCount; i++)
		{
			ret += *sources[i];
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

		for (int i = 0; i < sourceCount; i++)
		{
			ret += *sources[i];
		}

		return ret / sourceCount;
	}

	T offset;
};