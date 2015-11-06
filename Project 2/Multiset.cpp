//Theodore Nguyen 704-156-701

#include "Multiset.h"
#include <iostream>
using namespace std;

Multiset::Multiset()
: m_size(0), m_uniqueSize(0)		//initialize member private vars with list
{
	m_head = new Node;				//create a dummy node
	m_head->m_before = m_head;		//set the pointers of the dummy node equal to m_head for circular doubly linked list
	m_head->m_next = m_head;
}

Multiset::~Multiset()
{
	Node* temp = m_head;
	//if the set is the empty set
	if (m_head->m_next == m_head && m_head->m_before == m_head->m_before)
	{
		delete m_head;
		return;
	}
	//if the set has size 1
	if (m_head->m_next == m_head->m_before && m_head->m_next != m_head && m_head->m_next != m_head)
	{
		delete m_head->m_next;
		delete m_head;
		return;
	}
	for (m_head = m_head->m_next; m_head != temp;)		//for all other cases
	{
		Node *temp2 = m_head->m_next;
		delete m_head;
		m_head = temp2;
	}
	delete m_head;
}

Multiset::Multiset(const Multiset& other)
{

	m_uniqueSize = other.m_uniqueSize;		//set member variables equal to that of other; these are not pointers, so no problems
	m_size = other.m_size;

	m_head = new Node;				//as in default constructor, define the dummy node and set circularity
	m_head->m_before = m_head;
	m_head->m_next = m_head;

	Node* ptr = m_head->m_next;				//define two pointers; one to traverse other, the other to initialize our multiset
	Node* thtptr = other.m_head->m_next;
	
	for (; thtptr != other.m_head; thtptr = thtptr->m_next, ptr = ptr->m_next) //exits the loop when other has re-reached its head
	{											//incremenent both pointers after each iteration
		ptr->m_next = new Node;
		ptr->m_next->m_data = thtptr->m_data;			//1) creates a new node
		ptr->m_next->m_count = thtptr->m_count;			//2) sets that new node's m_data and m_count equal to other's
		ptr->m_next->m_before = ptr;					//3) sets that new node's before pointer equal to the current 
	}				//upon exiting the loop, the last new node has unintialized m_next, and the dummy node's m_before still points to head
	ptr->m_next = m_head;				//this takes care of that.
	m_head->m_before = ptr;
}

Multiset& Multiset::operator=(const Multiset& other)
{
	if (this != &other)
	{	//1) copying the destructor
		Node* temp = m_head;
		//if the set is the empty set
		if (m_head->m_next == m_head && m_head->m_before == m_head->m_before)
		{
			delete m_head;
		}
		//if the set has size 1
		else if (m_head->m_next == m_head->m_before && m_head->m_next != m_head && m_head->m_next != m_head)
		{
			delete m_head->m_next;
			delete m_head;
		}
		else
		for (m_head = m_head->m_next; m_head != temp;)
		{
			Node *temp2 = m_head->m_next;
			delete m_head;
			m_head = temp2;
		}
		delete m_head;



		//2) copying the copy constructor
		m_uniqueSize = other.m_uniqueSize;
		m_size = other.m_size;

		m_head = new Node;
		m_head->m_before = m_head;
		m_head->m_next = m_head;

		Node* ptr = m_head->m_next;
		Node* thtptr = other.m_head->m_next;

		for (; thtptr != other.m_head; thtptr = thtptr->m_next, ptr = ptr->m_next)
		{
			ptr->m_next = new Node;
			ptr->m_next->m_data = thtptr->m_data;
			ptr->m_next->m_count = thtptr->m_count;
			ptr->m_next->m_before = ptr;
		}
		ptr->m_next = m_head;
		m_head->m_before = ptr;
	}

	//3) returning *this.
	return *this;

}

bool Multiset::empty() const
{
	if (m_uniqueSize == 0 && m_size == 0)
		return true;
	else
		return false;

}

int Multiset::size() const
{
	return m_size;
}

int Multiset::uniqueSize() const
{
	return m_uniqueSize;
}

bool Multiset::insert(const ItemType& value)
{

	Node* temp;		//traverser
	for (temp = m_head->m_next; temp != m_head; temp = temp->m_next)	//if it exists in the multiset, just increment
	{
		if (temp->m_data == value)
		{
			temp->m_count++;
			m_size++;
			return true;
		}
	}								//otherwise, if it doesn't exist in the multiset..
	if (m_size == 0)			
	{
		Node* newNode = new Node;			//if there are no nodes - that is, only the head and the dummy node exist
		newNode->m_data = value;
		newNode->m_count = 1;
		newNode->m_next = m_head;
		m_head->m_next = newNode;
		m_head->m_before = newNode;
		newNode->m_before = m_head;
		m_size++;
		m_uniqueSize++;
		return true;
	}
	else
	{
		Node* newNode = new Node;					//case for where there are existing nodes
		newNode->m_data = value;
		newNode->m_count = 1;
		newNode->m_next = m_head;	/// ->m_next;
		newNode->m_before = m_head->m_before;
		m_head->m_before->m_next = newNode;	////
		m_head->m_before = newNode;
		//newNode->m_before = newNode;
		m_size++;
		m_uniqueSize++;
		return true;
	}
	/*
	Node* newNode = new Node;
	newNode->m_data = value;
	newNode->m_count = 1;
	newNode->m_next = m_head->m_next;
	newNode->m_before = m_head;
	m_head->m_next = newNode;
	newNode->m_before = newNode;
	m_size++;
	m_uniqueSize++;
	return true;*/

}

int Multiset::erase(const ItemType& value)
{
	for (Node* temp = m_head->m_next; temp != m_head; temp = temp->m_next)		//traverse the array, searching for value
	{
		if (temp->m_data == value)			//if value is found
		{
			if (temp->m_count != 1)		//if subtracting one from value will not set its count = 0, subtract 1 and exit
			{
				temp->m_count--;
				m_size--;
				return 1;
			}
			else if (temp->m_count == 1)		//if subtracting one from value will set count = 0, must delete the node
			{
				Node* storage = temp;		//store the node we are going to delete
				temp->m_before->m_next = temp->m_next;	//have the node before and the node after point to each other
				temp->m_next->m_before = temp->m_before;		//^^ is why we need to store, or else cant access the node to delete
				delete storage;		//delete the node
				m_size--;
				m_uniqueSize--;
				return 1;
			}
		}
	}
	return 0;
}

int Multiset::eraseAll(const ItemType& value)
{
	for (Node* temp = m_head->m_next; temp != m_head; temp = temp->m_next)
	{
		if (temp->m_data == value)
		{
			m_size = m_size - temp->m_count;			//essenitially works exactly the same as erase fcn's case when a node is deleted
			m_uniqueSize--;
			int count = temp->m_count;
			Node* storage = temp;
			temp->m_before->m_next = temp->m_next;
			temp->m_next->m_before = temp->m_before;
			delete storage;
			return count;
		}
	}
	return 0;
}

bool Multiset::contains(const ItemType& value) const
{
	for (Node* temp = m_head->m_next; temp != m_head; temp = temp->m_next)
	{
		if (temp->m_data == value)
			return true;
	}
	return false;
}

int Multiset::count(const ItemType& value) const
{
	for (Node* temp = m_head->m_next; temp != m_head; temp = temp->m_next)
	{
		if (temp->m_data == value)
			return temp->m_count;
	}
	return 0;
}

int Multiset::get(int i, ItemType& value) const
{
	if (i < 0 || i >= m_uniqueSize)			//check boundary conditions
		return 0;
	else
	{
		int j = 0;			//create traversers for determining which value to look at, and to traverse
		Node* temp = m_head->m_next;
		for (; temp != m_head; temp = temp->m_next, j++)
		{
			if (j == i)			//just traverse the list, incrementing the traverser until it is at the desired "index"
			{
				value = temp->m_data;
				return temp->m_count;
			}
		}
	}
	return 0;
}


void Multiset::swap(Multiset& other)
{
	Node* temp = m_head;			//creates a temp 3 times to swap variables. 
	m_head = other.m_head;			//the integer swapping is elementarily self-explanatory
	other.m_head = temp;		//we can swap the linked lists because there will be no deletions, as no two pointers point to same list

	int sizetemp = m_size;
	m_size = other.m_size;
	other.m_size = sizetemp;

	int uniquetemp = m_uniqueSize;
	m_uniqueSize = other.m_uniqueSize;
	other.m_uniqueSize = uniquetemp;
}

void Multiset::dump()		//test function essentially outputs all of the linked list; called in main whenever I call another fcn
{
	for (Node* temp = m_head->m_next; temp != m_head; temp = temp->m_next)
	{
		cerr << temp->m_data << " " << temp->m_count << "|" << m_size << "|" << m_uniqueSize << endl;
	}
}

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
	result = ms1;		//set results values to that of ms1, so we dont have to traverse and add them to it. 
	for (int i = 0; i != ms2.uniqueSize(); i++)//also, if result is very large, traversing wouldn't even work as it will still contain elements of result
	{
		ItemType x;				//from having a result essentially the same as ms1, we traverse ms2 and use get to retrieve values, and insert them to result
		ms2.get(i, x);
		for (int num = 0; num != ms2.count(x); num++)
			result.insert(x);
	}
}

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
	result = ms1;		//sets result to ms1; since the output of this can only have values of ms1 anyway

	for (int i = 0; i < ms2.uniqueSize(); i++)		
	{				//traverses ms2; if there is a value in ms2 that is in result, erases that value that many times from result
		ItemType x;
		for (int k = 0; k < ms2.get(i, x); k++)
		{
			result.erase(x);
		}
	}
}
