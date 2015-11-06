//Theodore Nguyen 704-156-701

#ifndef MULTISET_INCLUDED
#define MULTISET_INCLUDED

using namespace std;
#include <string>
typedef std::string ItemType;
//typedef unsigned long ItemType;

class Multiset
{
public:
	Multiset();
	~Multiset();
	Multiset(const Multiset& other);
	Multiset& operator=(const Multiset& other);
	bool empty() const;
	int size() const;
	int uniqueSize() const;
	bool insert(const ItemType& value);
	int erase(const ItemType& value);
	int eraseAll(const ItemType& value);
	bool contains(const ItemType& value) const;
	int count(const ItemType& value) const;
	int get(int i, ItemType& value) const;
	void swap(Multiset& other);

	void dump();
private:
	struct Node
	{
		ItemType m_data;
		int m_count;
		Node* m_next;
		Node* m_before;
	};
	Node* m_head;
	int m_size;
	int m_uniqueSize;
};

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);
void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);

#endif // MULTISET_INCLUDED