# 14. 最长公共前缀

## 问题
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。
```
示例 1:
输入: ["flower","flow","flight"]
输出: "fl"
```
```
示例 2:
输入: ["dog","racecar","car"]
输出: ""
解释: 输入不存在公共前缀。
```
说明:
所有输入只包含小写字母 a-z 。

## 解题思路
思路很简单，就是一个一个比较
```cpp
string longestCommonPrefix(vector<string>& strs) {
    if(strs.empty())
        return "";
    if(strs.size() == 1)
        return strs[0];  
    
    // 以第一个字符串为标准进行比较
    for (int i = 0; i < strs[0].size(); ++i)
    {
        // 接着逐个比较其他字符串
        for (int j = 1; j < strs.size(); ++j)
        {
            // 当要比较的字符串已经到最后一个字符了，或者不相等了，就返回目前为止公共的部分
            if ((i >= strs[j].size()) || strs[j][i] != strs[0][i])
            {
                return strs[0].substr(0, i);
            }
        }
    }
    return strs[0];
}
```