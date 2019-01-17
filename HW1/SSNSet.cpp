#include <iostream>

#include "SSNSet.h"

SSNSet::SSNSet()
{
	//no need to initialize any member variables
}

bool SSNSet::add(unsigned long ssn)
{
	return m_set.insert(ssn);
}

int SSNSet::size() const
{
	return m_set.size();
}

void SSNSet::print() const
{
	unsigned long temp;
	for (int i = 0; i < size(); i++)
	{
		m_set.get(i, temp);
		std::cout << temp << std::endl;
	}
}