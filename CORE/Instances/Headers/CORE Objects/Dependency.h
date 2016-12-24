#pragma once
template<typename T>
struct Dependency
{
	T* data;
	Dependency* dependencies;
	int dependencyCount;

	void operator=(T value)
	{
		if (data)
		{
			//Pass the difference on to dependencies if they exist
			if (dependencies)
			{
				T difference = value - *pointer;

				for (int i = 0; i < dependencyCount; i++)
				{
					Dependency* child = dependencies + i;
					chiild->data += difference;
				}
			}

			*data = value;
		}
	}
};