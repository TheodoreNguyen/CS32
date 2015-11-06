#include <iostream> 
#include <cassert>
#include "Multiset.h"
using namespace std;

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }

void thisFunctionWillNeverBeCalled()
{
	Multiset();
	(Multiset(Multiset()));
	CHECKTYPE(&Multiset::operator=, Multiset& (Multiset::*)(const ItemType&));
	CHECKTYPE(&Multiset::empty, bool (Multiset::*)() const);
	CHECKTYPE(&Multiset::size, int  (Multiset::*)() const);
	CHECKTYPE(&Multiset::uniqueSize, int  (Multiset::*)() const);
	CHECKTYPE(&Multiset::insert, bool (Multiset::*)(const ItemType&));
	CHECKTYPE(&Multiset::erase, int  (Multiset::*)(const ItemType&));
	CHECKTYPE(&Multiset::eraseAll, int  (Multiset::*)(const ItemType&));
	CHECKTYPE(&Multiset::contains, bool (Multiset::*)(const ItemType&) const);
	CHECKTYPE(&Multiset::count, int  (Multiset::*)(const ItemType&) const);
	CHECKTYPE(&Multiset::get, int  (Multiset::*)(int, ItemType&) const);
	CHECKTYPE(&Multiset::swap, void (Multiset::*)(Multiset&));
	CHECKTYPE(combine, void(*)(const Multiset&, const Multiset&, Multiset&));
	CHECKTYPE(subtract, void(*)(const Multiset&, const Multiset&, Multiset&));
}


void test()
{
	Multiset sms;
	assert(sms.insert("cumin"));
	assert(sms.insert("turmeric"));
	assert(sms.insert("cumin"));
	assert(sms.insert("coriander"));
	assert(sms.insert("cumin"));
	assert(sms.insert("turmeric"));
	assert(sms.size() == 6 && sms.uniqueSize() == 3);
	assert(sms.count("turmeric") == 2);
	assert(sms.count("cumin") == 3);
	assert(sms.count("coriander") == 1);
	assert(sms.count("cardamom") == 0);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}

/*
int main()
{
	Multiset ulms;
	assert(ulms.insert(20));
	assert(ulms.insert(10));
	assert(ulms.insert(20));
	assert(ulms.insert(30));
	assert(ulms.insert(20));
	assert(ulms.insert(10));
	assert(ulms.size() == 6 && ulms.uniqueSize() == 3);
	assert(ulms.count(10) == 2);
	assert(ulms.count(20) == 3);
	assert(ulms.count(30) == 1);
	assert(ulms.count(40) == 0);
	Multiset a;
	a.dump();
	cerr << endl << "-------------------" << endl << endl;
	a.insert(10);
	a.dump();
	cerr << endl << "-------------------" << endl << endl;
	a.insert(10);
	a.insert(10);
	a.insert(200);
	a.insert(200);
	a.insert(10000);
	a.dump();
	for (int k = 0; k < a.uniqueSize(); k++)
	{
		ItemType x;
		int n = a.get(k, x);
		cerr << x << " occurs " << n << " times." << endl;
	}
	a.dump();
	cerr << endl << "-------------------" << endl << endl;
	a.erase(10);
	a.insert(125);
	a.insert(125);
	assert(a.count(125) == 2);
	a.dump();
	cerr << endl << "-------------------" << endl << endl;
	a.erase(10000);
	a.eraseAll(125);
	cerr << a.erase(123121) << endl;
	a.dump();
	assert(!a.contains(ItemType(1261)));
	assert(a.contains(200));
	assert(a.count(200) == 2);


	Multiset ms;
	assert(ms.empty());
	unsigned long x = 999;
	assert(ms.get(0, x) == 0 && x == 999);  // x unchanged by get failure
	assert(!ms.contains(42));
	ms.insert(42);
	ms.insert(42);
	assert(ms.size() == 2 && ms.uniqueSize() == 1);
	assert(ms.get(1, x) == 0 && x == 999);  // x unchanged by get failure
	assert(ms.get(0, x) == 2 && x == 42);
	cerr << "Passed all tests" << endl;

	cerr << "---------" << endl;

	Multiset d(ms);   // a can hold at most 1000 distinct items
	Multiset b(a);      // b can hold at most 5 distinct items
	Multiset c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
	ItemType v[6] = { 1, 2, 3, 4, 5, 6 };
	// No failures inserting 5 distinct items twice each into b
	for (int k = 0; k < 5; k++)
	{
		assert(b.insert(v[k]));
		assert(b.insert(v[k]));
	}
	b.dump();
	cerr << "-----------" << endl;
	// When two Multisets' contents are swapped, their capacities are swapped
	// as well:
	a.swap(b);
	b.dump();

	cerr << "-----------" << endl;
	Multiset ms1;
	ms1.insert(2);
	ms1.insert(2);
	ms1.insert(2);
	ms1.insert(8);
	ms1.insert(3);
	ms1.insert(3);
	ms1.insert(9);
	ms1.insert(5);
	ms1.dump();

	Multiset ms2;
	ms2.insert(6);
	ms2.insert(3);
	ms2.insert(8);
	ms2.insert(8);
	ms2.insert(5);
	ms2.insert(10);
	ms2.dump();
	cerr << "-----" << endl;
	a.dump();
	cerr << "-------------" << endl;
	Multiset result(ms2);
	result.dump();
	cerr << "-----------------" << endl;
	result = ms1;
	result.dump();
	cerr << "---------------" << endl;
	combine(ms1, ms2, result);
	result.dump();

	cerr << "-----------" << endl;
	subtract(ms1, ms2, result);

	result.dump();
}
*/