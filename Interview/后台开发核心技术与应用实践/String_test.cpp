#include <iostream>
#include "String.hpp"

using namespace std;

int main()
{
    String test("This is String test");
    test.print();
    cout << endl;

    String copy(test);
    copy.print();
    cout << endl;

    String assign = test;
    assign.print();
    cout << endl;

    String add = test + copy;
    add.print();
    cout << endl;

    // cout << (test == copy) << endl;
    // cout << test.size() << endl;
}
