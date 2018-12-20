// 面试题31：栈的压入、弹出序列
// 题目：输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是
// 否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1、2、3、4、
// 5是某栈的压栈序列，序列4、5、3、2、1是该压栈序列对应的一个弹出序列，但
// 4、3、5、1、2就不可能是该压栈序列的弹出序列。

class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        if(!pushV.empty() && !popV.empty())
        {
            stack<int> s;
            auto it1 = pushV.begin();
            auto it2 = popV.begin();
            
            while(it2 != popV.end())
            {
                while(s.empty() || s.top() != *it2)
                {
                    s.push(*it1);
                    ++it1;
                }
                
                if(s.top() != *it2)
                {
                    break;
                }
                
                s.pop();
                ++it2;
            }
            
            if(it1 == pushV.end())
            {
                return true;
            }
        }
        
        return false;
    }
};