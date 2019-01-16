// 面试题45：把数组排成最小的数
// 题目：输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼
// 接出的所有数字中最小的一个。例如输入数组{3, 32, 321}，则打印出这3个数
// 字能排成的最小数字321323。

class Solution {
public:
    string PrintMinNumber(vector<int> numbers) {
        if(numbers.empty())
        {
            return string();
        }
        
        vector<string> vs;
        for(int n : numbers)
        {
            vs.push_back(to_string(n));
        }
        
        sort(vs.begin(), vs.end(), compare);
        
        string ret;
        for(string s : vs)
        {
            ret += s;
        }
        
        return ret;
    }
    
    static bool compare(const string& s1, const string &s2)
    {
        string tmp1 = s1 + s2;
        string tmp2 = s2 + s1;
        return tmp1 < tmp2;
    }
};