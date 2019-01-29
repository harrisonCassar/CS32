#include "Set.h"
#include <iostream>
#include <cassert>

using namespace std;

void test()
{
    Set s1;

    assert(s1.insert("roti"));
    assert(s1.insert("pita"));
    assert(s1.size() == 2);
    assert(s1.contains("pita"));

    ItemType x = "laobing";
    assert(s1.get(0, x) && x == "pita");
    assert(s1.get(1, x) && x == "roti");

    //default constructor
    Set ss;

    //for an empty set
    assert(s1.size() == 0);             //test size
    assert(s1.empty());                 //test empty
    assert(!s1.erase("roti"));          //nothing to remove 

    //functions of one set
    assert(s1.insert("roti"));          //test insert
    assert(s1.insert("pita"));          //test insert again
    assert(s1.size() == 2);             //test size
    assert(!s1.empty());                //test empty
    assert(s1.contains("pita"));        //test contains on a present value
    assert(!s1.contains("spaghetti"));   //test contains on a non-present value
    assert(s1.erase("roti"));          //test erase on present value
    assert(!s1.erase("spaghetti"));          //test erase on present value
    assert(s1.insert("shells"));          //insert another element for later tests
    

    //copy constructor
    Set s2(s1);

    //assignment operator
    Set s3;
    assert(s3 = s2 == &s3);




}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}