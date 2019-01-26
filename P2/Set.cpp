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
	src.get(0,tempValue);

	//properly assign first Node's members
	m_head->value = tempValue;
	m_head->prev = m_head->next = nullptr;

	for (int i = 1; i < src.size(); i++)
	{
		//create a Node to be added
		tempPtr = new Node;

		//set new Node's members
		src.get(i,tempValue);
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
		delete head;
		return;
	}

	//temporary pointer for traversing linked list
	Node* tempPtr = head->next;

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
	//check for already present value or full set capacity
	if (contains(value) || size() >= DEFAULT_MAX_ITEMS)
		return false;

	//temp ItemType variable that allows for compatibility with the class Set's "get()" member function
	ItemType temp;

	//counting variable to track current iterating position
	int index;

	//iterate through set starting from the beginning
	for (index = 0; index < size(); index++)
	{
		//set temp's value to the current element in the sorted set
		get(index, temp);

		//break condition: if temp is greater than inputted value, begin insertion immediately
		if (value < temp)
		{
			break;
		}
	}

	//shift all values of set to the right, making room for new value to be inserted
	for (int j = size(); j != index; j--)
	{
		m_elements[j] = m_elements[j - 1];
	}

	//set value to its properly sorted position
	m_elements[index] = value;

	//increment set's total size
	m_size++;

	return true;
}

bool Set::erase(const ItemType& value)
{
	//counting variable to track current iterating position
	int index;

	//iterate through array until finding match with value (break condition) or until end of set
	for (index = 0; index < size(); index++)
	{
		if (value == m_elements[index])
			break;
	}

	//an index matching the size indicates no matches were found (do not modify, and return false)
	if (index == size())
		return false;

	//overwrite next element value into previous element value for entire length of set
	for (int i = index; i < size()-1; i++)
	{
		m_elements[i] = m_elements[i + 1];
	}

	//decrement set's total size (this additionally 
	m_size--;

	return true;
}

bool Set::contains(const ItemType& value) const
{
	//iterate through set, returning true if finding a match to the inputted value
	for (int i = 0; i < size(); i++)
	{
		if (value == m_elements[i])
			return true;
	}

	return false;
}

bool Set::get(int i, ItemType& value) const
{
	//check if i is within current boundaries of set
	if (i < 0 || i >= size())
		return false;

	//since set is already sorted from least to greatest, can access value of interest using i as the index of the array
	value = m_elements[i];

	return true;
}

void Set::swap(Set& other)
{
	ItemType temp;
	int threshold;

	//find highest size and record it (used for knowing when to stop swapping values)
	if (m_size >= other.m_size)
		threshold = m_size;
	else
		threshold = other.m_size;

	//iterate through sets, swapping each value
	for (int i = 0; i < threshold; i++)
	{
		temp = m_elements[i];
		m_elements[i] = other.m_elements[i];
		m_elements[i] = temp;
	}

	//switch the sizes of each set after swapping all values within the sizes
	int tempsize = other.m_size;
	other.m_size = m_size;
	m_size = tempsize;
}

void Set::dump() const
{
	//iterate through set, printing all values
	for (int i = 0; i < size(); i++)
	{
		std::cerr << m_elements[i] << std::endl;
	}
}