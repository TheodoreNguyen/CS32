#include "Multiset.h"
#include <iostream>
using namespace std;

Multiset::Multiset()
{
	item m_array[DEFAULT_MAX_ITEMS];
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		m_array[i].count = 0;
	}
}

bool Multiset::empty() const
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_array[i].count != 0)
			return false;
	}
	return true;
}

int Multiset::size() const
{
	int size = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
		size += m_array[i].count;
	return size;
}


int Multiset::uniqueSize() const
{
	int size = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_array[i].count > 0)
			size++;
	}
	return size;
}

bool Multiset::insert(const ItemType& value)
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_array[i].something == value)
		{
			m_array[i].count++;
			return true;
		}
	}
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_array[i].count == 0)
		{
			m_array[i].something = value;
			m_array[i].count++;
			return true;
		}
	}
	return false;
}

int Multiset::erase(const ItemType& value)
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_array[i].something == value)
		{
			if (m_array[i].count > 0)
			{
				m_array[i].count--;
				return 1;
			}
		}
	}
	return 0;
}

int Multiset::eraseAll(const ItemType& value)
{
	int numberErased = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_array[i].something == value)
		{
			numberErased = m_array[i].count;
			m_array[i].count = 0;
		}
	}
	return numberErased;
}

bool Multiset::contains(const ItemType& value) const
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_array[i].something == value)
		if (m_array[i].count > 0)
			return true;
	}
	return false;
}

int Multiset::count(const ItemType& value) const
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_array[i].something == value)
			return m_array[i].count;
	}
	return 0;
}

int Multiset::get(int i, ItemType& value) const
{
	if (i >= 0 && i < uniqueSize())
	if (m_array[i].count > 0)
	{
		value = m_array[i].something;
		return m_array[i].count;
	}
	return 0;
}

void Multiset::swap(Multiset& other)
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		item temp = m_array[i];
		m_array[i] = other.m_array[i];
		other.m_array[i] = temp;
	}
}

void Multiset::dump() const
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		cerr << m_array[i].something << endl << m_array[i].count << endl << endl;
	}
	cerr << "---------------------" << endl;
}