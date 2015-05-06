#include "StudentMultiset.h"
#include <iostream>
#include "Multiset.h"
using namespace std;

StudentMultiset::StudentMultiset()
{
	Multiset m_sID;
}

bool StudentMultiset::add(unsigned long id)
{
	return m_sID.insert(id);
}

int StudentMultiset::size() const
{
	return m_sID.size();
}

void StudentMultiset::print() const
{
	for (int i = 0; i != DEFAULT_MAX_ITEMS; i++)
	{
		ItemType x;
		int n = m_sID.get(i, x);
		for (int j = 0; j != n; j++)
		{
			cout << x << endl;
		}
	}
}
