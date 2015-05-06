#include "newMultiset.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Multiset::Multiset()
{
	m_array = new item[DEFAULT_MAX_ITEMS];
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		m_array[i].count = 0;
	}
	m_max = DEFAULT_MAX_ITEMS;
}

Multiset::Multiset(int maximum)
{
	if (maximum < 0)
	{
		cout << "Cannot input a negative number\n";
		exit(1);
	}
	m_array = new item[maximum];
	for (int i = 0; i < maximum; i++)
	{
		m_array[i].count = 0;
	}
	m_max = maximum;
}

Multiset::Multiset(const Multiset& other)
{
	m_array = new item[other.m_max];
	for (int i = 0; i != other.m_max; i++)
	{
		m_array[i].something = other.m_array[i].something;
		m_array[i].count = other.m_array[i].count;
	}
	m_max = other.m_max;
}

Multiset::~Multiset()
{
	delete [] m_array;
}

Multiset& Multiset::operator=(const Multiset& rhs)
{
	/*if (this != &rhs)
	{
		delete [] m_array;
		item* m_array = new item[DEFAULT_MAX_ITEMS];
		for (int i = 0; i != DEFAULT_MAX_ITEMS; i++)
		{
			m_array[i].something = rhs.m_array[i].something;
			m_array[i].count = rhs.m_array[i].count;
		}
	}
	return this;*/
	Multiset temp(rhs);
	swap(temp);
	return *this;
}

bool Multiset::empty() const
{
	for (int i = 0; i < m_max; i++)
	{
		if (m_array[i].count != 0)
			return false;
	}
	return true;
}

int Multiset::size() const
{
	int size = 0;
	for (int i = 0; i < m_max; i++)
		size += m_array[i].count;
	return size;
}


int Multiset::uniqueSize() const
{
	int size = 0;
	for (int i = 0; i < m_max; i++)
	{
		if (m_array[i].count > 0)
			size++;
	}
	return size;
}

bool Multiset::insert(const ItemType& value)
{
	for (int i = 0; i < m_max; i++)
	{
		if (m_array[i].something == value)
		{
			m_array[i].count++;
			return true;
		}
	}
	for (int i = 0; i < m_max; i++)
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
	for (int i = 0; i < m_max; i++)
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
	for (int i = 0; i < m_max; i++)
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
	for (int i = 0; i < m_max; i++)
	{
		if (m_array[i].something == value)
		if (m_array[i].count > 0)
			return true;
	}
	return false;
}

int Multiset::count(const ItemType& value) const
{
	for (int i = 0; i < m_max; i++)
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
	item* temp = m_array;
	m_array = other.m_array;
	other.m_array = temp;
	
	int maxtemp = m_max;
	m_max = other.m_max;
	other.m_max = maxtemp;
}

void Multiset::dump() const
{
	for (int i = 0; i < m_max; i++)
	{
		cerr << m_array[i].something << endl << m_array[i].count << endl << endl;
	}
	cerr << "---------------------" << endl;
	
}