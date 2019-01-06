// 面试题38：字符串的排列
// 题目：输入一个字符串，打印出该字符串中字符的所有排列。例如输入字符串abc，
// 则打印出由字符a、b、c所能排列出来的所有字符串abc、acb、bac、bca、cab和cba。



class Solution {
public:
    vector<string> Permutation(string str) {
        vector<string> ret;
        if(str.empty())
        {
            return ret;
        }
        
        Permutation(ret, str, 0);
        sort(ret.begin(), ret.end());
        return ret;
    }
    
    void Permutation(vector<string>& ret, string str, int begin)
    {
        if(begin == str.size()-1)
        {
            ret.push_back(str);
            return;
        }
        
        for(int i = begin; i < str.size(); ++i)
        {
            // 避免重复
            if(begin != i && str[begin] == str[i])
            {
                continue;
            }
            
            swap(str[i], str[begin]);
            
            Permutation(ret, str, begin+1);
            
            swap(str[i], str[begin]);
        }
    }
};