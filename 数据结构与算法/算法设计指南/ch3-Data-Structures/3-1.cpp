#include <iostream>
#include <stack>
#include <string>

using namespace std;

void check(string input)
{
    stack<int> parens;

    for(unsigned int i = 0; i < input.size(); ++i)
    {
        char ch = input[i];
        if(ch == ')')
        {
            if(parens.empty())
            {
                cout << "unmatched ')' at position: " << i << endl;
                return;
            }
            parens.pop();
        }
        else if(ch == '(')
        {
            parens.push(i);
        }
    }


    if(!parens.empty())
    {
        while(parens.size() > 1)
        {
            parens.pop();
        }
        cout << "unmatched '(' at position: " << parens.top() << endl;
        return;
    }
    else
    {
        cout << "parens balanced!" << endl;
    }
}

int main(){
    check("((()))");
    check("((())()");
    check("()))");
    return 0;
}
