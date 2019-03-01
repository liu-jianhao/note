#include "LinkList.hpp"

int main()
{
    LinkList<int> link;
    for(int i = 0; i < 10; ++i)
    {
        link.push(i);
    }
    link.display();

    link.pop();
    link.display();

    link.insert(100, 3);
    link.display();

}
