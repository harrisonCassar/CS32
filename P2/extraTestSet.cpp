#include "Set.h"
#include <iostream>
#include <cassert>

using namespace std;

void test()
{
    Set ss;
    cout << "1" << endl;
    assert(ss.insert("roti"));
    cout << "2" << endl;
    assert(ss.insert("pita"));
    cout << "3" << endl;
    assert(ss.size() == 2);
    cout << "4" << endl;
    assert(ss.contains("pita"));
    cout << "5" << endl;
    ItemType x = "laobing";
    cout << "6" << endl;
    assert(ss.get(0, x) && x == "pita");
    cout << "7" << endl;
    assert(ss.get(1, x) && x == "roti");
    cout << "8" << endl;
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}