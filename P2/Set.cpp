#include <iostream>

#include "Set.h"

Set::Set()
{
	m_head = m_tail = nullptr;
	m_size = 0;
}

Set::Set(const Set& src)
{
	if (src.size() == 0)
		return;

	//assign head and tail to the first new node
	m_head = m_tail = new Node;

	//declare temp variables
	ItemType tempValue;
	Node* tempPtr = m_head; //will point to new one being added

	//get value of first Node in source
	src.get(0, tempValue);

	//properly assign first Node's members
	m_head->value = tempValue;
	m_head->prev = m_head->next = nullptr;

	for (int i = 1; i < src.size(); i++)
	{
		//create a Node to be added
		tempPtr = new Node;

		//set new Node's members
		src.get(i, tempValue);
		tempPtr->value = tempValue;
		tempPtr->prev = m_tail;
		tempPtr->next = nullptr;

		//update next pointer of the previously "last" Node
		m_tail->next = tempPtr;

		//update tail
		m_tail = tempPtr;
	}

	//set final size
	m_size = src.size();
}

Set::~Set()
{
	if (size() == 0)
		return;

	if (size() == 1)
	{
		delete m_head;
		return;
	}

	//temporary pointer for traversing linked list
	Node* tempPtr = m_head->next;

	//traverse linked list, deleting each Node
	while (tempPtr->next != nullptr)
	{
		delete tempPtr->prev;
		tempPtr = tempPtr->next;
	}

	//special steps taken for last Node to ensure delete is not called improperly
	delete tempPtr->prev;
	delete tempPtr;
}

Set& Set::operator=(const Set& src)
{
	if (this != &src)
	{
		Set temp(src);
		this->swap(temp);
	}

	return *this;
}

bool Set::empty() const
{
	if (size() == 0)
		return true;
	else
		return false;
}

int Set::size() const
{
	return m_size;
}

bool Set::insert(const ItemType& value)
{
	//check for already present value
	if (contains(value))
		return false;

	//declare temp variables for compatibility with Set's other member functions
	ItemType tempValue;
	Node* tempPtr;

	//counting variable to track current iterating position
	int index;

	//iterate through set starting from the beginning
	for (index = 0; index < size(); index++)
	{
		//set temp's value to the current element in the sorted set
		get(index, tempValue);

		//break condition: if temp is greater than inputted value, begin insertion immediately
		if (value < tempValue)
		{
			break;
		}
	}

	//set value to its properly sorted position, with special cases at beginning and end
	if (index == 0)
	{
		//check special case where adding to empty list
		if (m_head == nullptr)
		{
			m_head = new Node;
			m_head->prev = nullptr;
			m_head->next = nullptr;
			m_head->value = value;

			//update tail
			m_tail = m_head;

			//update size
			m_size++;

			return true;
		}

		//properly reassign pointers with the addition of a new Node at the front of the list
		tempPtr = m_head;
		m_head = new Node;
		m_head->prev = nullptr;
		m_head->next = tempPtr;
		tempPtr->prev = m_head;
		m_head->value = value;

		//update size
		m_size++;

		return true;
	}

	//special case for inserting value at end of list
	if (index == size())
	{
		//properly reassign pointers with the addition of a new Node at the end of the list
		tempPtr = m_tail;
		m_tail = new Node;
		m_tail->prev = tempPtr;
		m_tail->next = nullptr;
		tempPtr->next = m_tail;
		m_tail->value = value;

		//update size
		m_size++;

		return true;
	}

	tempPtr = m_head;

	for (int i = 0; i < index; i++)
	{
		tempPtr = tempPtr->next;
	}
	
	//updates all affected pointers on existing preceding Node, new Node, and succeeding Node (and the value for the new Node)
	tempPtr->prev->next = new Node;
	tempPtr->prev->next->prev = tempPtr->prev;
	tempPtr->prev->next->next = tempPtr;
	tempPtr->prev = tempPtr->prev->next;
	tempPtr->prev->value = value;

	//increment set's total size
	m_size++;

	return true;
}

bool Set::erase(const ItemType& value)
{
	//check for empty list
	if (m_head == nullptr)
		return false;

	//special case check for deleting first item in list
	if (m_head->value == value)
	{
		//temporary pointer for pointing to erase's target Node
		Node* killPtr = m_head;

		//special case for a one-Node linked list
		if (m_head->next == nullptr)
		{
			delete killPtr;

			//update head/tail pointers
			m_head = nullptr;
			m_tail = nullptr;

			//update size
			m_size--;

			return true;
		}

		//update pointers of second Node in linked list
		m_head->next->prev = nullptr;
		m_head = m_head->next;
		
		//delete first Node
		delete killPtr;

		//update size
		m_size--;

		return true;
	}

	//temporary pointer for linked list traversal
	Node* tempPtr = m_head;

	//traverse through linked list until finding match with value (break condition) or until end of set
	while (tempPtr != nullptr)
	{
		if (tempPtr->next != nullptr && tempPtr->next->value == value)
			break;

		tempPtr = tempPtr->next;
	}

	//if we broke out on the target value (meaning we found it)
	if (tempPtr != nullptr)
	{
		//special case check for erasing last Node (for updating tail pointer)
		if (tempPtr == m_tail)
			m_tail = m_tail->prev;

		Node* killPtr = tempPtr->next;
		tempPtr->next = killPtr->next;
		tempPtr->next->prev = tempPtr;

		delete killPtr;
	}
	else
		return false;

	//decrement set's total size
	m_size--;

	return true;
}

bool Set::contains(const ItemType& value) const
{
	//begins temporary pointer at head for linked list traversal
	Node* tempPtr = m_head;

	//special check for value's presence in the first node of the linked list
	if (tempPtr != nullptr && tempPtr->value == value)
		return true;

	//traverse linked list, returning true if value is found
	while (tempPtr != nullptr)
	{
		if (tempPtr->next != nullptr && tempPtr->next->value == value)
			return true;

		tempPtr = tempPtr->next;
	}

	return false;
}

bool Set::get(int i, ItemType& value) const
{
	//check if i is within current boundaries of set
	if (i < 0 || i >= size())
		return false;

	//temporary pointer for linked list traversal
	Node* tempPtr = m_head;

	//traverse linked list to designated node
	for (int j = 0; j < i; j++)
		tempPtr = tempPtr->next;

	//since set is already sorted from least to greatest, can access value of interest using i as the number of Nodes "into" the linked list
	value = tempPtr->value;

	return true;
}

void Set::swap(Set& other)
{
	//temporary pointer for switching value of one head/tail pointer
	Node* tempPtr;
	int tempSize;

	//switch head pointers
	tempPtr = m_head;
	m_head = other.m_head;
	other.m_head = tempPtr;

	//switch tail pointers
	tempPtr = m_tail;
	m_tail = other.m_tail;
	other.m_tail = tempPtr;

	//switch the sizes of each set
	tempSize = m_size;
	m_size = other.m_size;
	other.m_size = tempSize;
}

void Set::dump() const
{
	//temporary pointer for linked list traversal
	Node* tempPtr = m_head;

	//iterate through set, printing all values
	while (tempPtr != nullptr)
	{
		std::cerr << tempPtr->value << std::endl;
		tempPtr = tempPtr->next;
	}
}

void unite(const Set& s1, const Set& s2, Set& result)
{
	//begin with result set having all values in s1
	result = s1;

	//temporary value for compatibility with Set's "get" member function
	ItemType tempValue;

	//traverse through s2 set, inserting values
	for (int i = 0; i < s2.size(); i++)
	{
		s2.get(i, tempValue);
		result.insert(tempValue);
	}
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
	//begin with result set having all values in s1
	result = s1;

	//temporary value for compatibility with Set's "get" member function
	ItemType tempValue;

	//traverse through s2 set, inserting values
	for (int i = 0; i < s2.size(); i++)
	{
		s2.get(i, tempValue);
		result.erase(tempValue);
	}
}
