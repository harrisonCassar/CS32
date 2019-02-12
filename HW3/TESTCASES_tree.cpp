#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
	double d1[4] = {1,2,3,4};
	double d2[2] = {3,2};

	assert(countIncludes(d1,4,d2,2) == 0);

	d2[0] = 2;
	d2[1] = 3;
	assert(countIncludes(d1,4,d2,2) == 1);

	//=====================================================================================================================================

	double u1[5] = {1,2,3,4,5};
	double u2[3] = {1,4,5};
	
	assert(countIncludes(u1,5,u2,3) == 1);
	
	u2[0] = 3;
	assert(countIncludes(u1,5,u2,3) == 1);

	u2[0] = 1;
	u2[1] = 2;
	u2[2] = 3;
	assert(countIncludes(u1,5,u2,3) == 1);

	//=====================================================================================================================================

	double s1[1] = {5};
	double s2[1] = {5};
	assert(countIncludes(s1,0,s2,1) == 0);
	assert(countIncludes(s1,0,s2,0) == 1);
	assert(countIncludes(s1,1,s2,0) == 1);

	s2[0] = {2};
	assert(countIncludes(s1,1,s2,1) == 0);

	double t1[2] = {10,20};
	double t2[3] = {10,20,30};

	assert(countIncludes(t1,2,t2,3) == 0);

	t2[1] = 10;
	assert(countIncludes(t1,2,t2,3) == 0);

	assert(countIncludes(t1,2,t2,2) == 0);

	t2[1] = 20;
	assert(countIncludes(t1,2,t2,2) == 1);

	//=====================================================================================================================================

	double testa1[6] = {10,10,10,10,10,10};
	double testa2[2] = {10,10};
	assert(countIncludes(testa1,6,testa2,2) == 15);

	//=====================================================================================================================================

	int n1 = 7;
	int n2 = 3;
	double a1[7] = {10,50,40,20,50,40,30};
	
	double a2[3] = {10,20,40};
	assert(countIncludes(a1,n1,a2,n2) == 1);

	a2[1] = 40;
	a2[2] = 30;
	assert(countIncludes(a1,n1,a2,n2) == 2);

	a2[0] = 20;
	a2[1] = 10;
	a2[2] = 40;
	assert(countIncludes(a1,n1,a2,n2) == 0);

	a2[0] = 50;
	a2[1] = 40;
	a2[2] = 30;
	assert(countIncludes(a1,n1,a2,n2) == 3);

	//=====================================================================================================================================

	cout << "uwu~? did my wittle cutie ELDON boi pass all of his tests? omg xd ezclap.. but i still like you as a friend... sort of ;)))))))))))))))))))))" << endl;
	return 0;
}