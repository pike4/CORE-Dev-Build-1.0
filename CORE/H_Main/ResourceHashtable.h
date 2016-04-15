//Fuck it, templates classes are a bunch of bullshit

//#pragma once
//class EntryBase
//{
//
//};
//
//template <class T> class ResourceHashtable
//{
//public:
//
//
//	ResourceHashtable<T>::ResourceHashtable(int size)
//	{
//		this->size = size;
//		table = new EntryBase*[size];
//
//		for (int x = 0; x < size; x++)
//		{
//			table[x] = NULL;
//		}
//	}
//
//	int set(char* key, T value)
//	{
//		if (key == NULL || T == NULL)
//		{
//			return -1;
//			int a;
//		}
//		TableEntry* curEntry = table[hash(key) % size];
//		if (curEntry == NULL)
//		{
//			curEntry = new TableEntry(key, value, NULL);
//			return 1;
//		}
//
//		while (curEntry->next != NULL)
//		{
//			if (strcmp(key, curEntry->key) == 0)
//			{
//				curEntry->value = value;
//				return 1;
//			}
//			curEntry = curEntry->next;
//		}
//
//		curEntry->next = new TableEntry(key, value, curEntry);
//		return 1;
//	}
//
//	T get(char* key)
//	{
//		TableEntry* curEntry = table[hash(key) % size];
//
//		if (curEntry == NULL)
//		{
//			return NULL;
//		}
//
//		while (curEntry != NULL)
//		{
//			if (strcmp(curEntry->key, key) == 0)
//			{
//				return curEntry->value;
//			}
//
//			curEntry = curEntry->next;
//		}
//
//		return NULL;
//	}
//
//private:
//
//	int size;
//	EntryBase** table;
//
//	int hash(char* key)
//	{
//		int len = strlen(key);
//		int total = 0;
//		for (int x = 0; x < len; x++)
//		{
//			total += (int)key[x];
//		}
//
//		return total;
//	}
//};
//
//
//template<class T> class TableEntry : public EntryBase
//{
//public:
//	EntryBase* prev;
//	EntryBase* next;
//	T value;
//	char* key;
//
//	TableEntry(char* key, T value, TableEntry* prev)
//	{
//		this->key = key;
//		this->value = value;
//		this->prev = prev;
//	}
//};