#include "SSNSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	SSNSet a;

	a.add(1910101);
	a.add(7777777);

	a.print();

	cout << a.size() << endl;

	return 0;
}