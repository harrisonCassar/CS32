#include "Set.h"

Set::Set()
{
	m_size = 0;
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
		elements[j] = elements[j - 1)];
	}

	//set value to its properly sorted position
	elements[index] = value;

	//increment the total size of the set
	m_size++;

	return true;
}

bool Set::erase(const ItemType& value)
{
	if (!contains(value))
		return false;


}

bool Set::contains(const ItemType& value) const
{
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

}