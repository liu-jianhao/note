// 面试题50（一）：字符串中第一个只出现一次的字符
// 题目：在字符串中找出第一个只出现一次的字符。如输入"abaccdeff"，则输出
// 'b'。

class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        if(str.empty())
            return -1;
        unordered_multiset<char> us;
        for(unsigned int i = 0; i < str.size(); ++i)
        {
            us.insert(str[i]);
        }
         
        for(unsigned int i = 0; i < str.size(); ++i)
        {
            if(us.count(str[i]) == 1)
                return i;
        }
        return -1;
    }
};