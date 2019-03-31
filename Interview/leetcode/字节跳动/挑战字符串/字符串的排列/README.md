# 字符串的排列
给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。

换句话说，第一个字符串的排列之一是第二个字符串的子串。

示例1:
```
输入: s1 = "ab" s2 = "eidbaooo"
输出: True
解释: s2 包含 s1 的排列之一 ("ba").
```

示例2:
```
输入: s1= "ab" s2 = "eidboaoo"
输出: False
```
 
注意：
输入的字符串只包含小写字母
两个字符串的长度都在 [1, 10,000] 之间

[博客](https://www.cnblogs.com/MrSaver/p/9638279.html)

## C++
```cpp
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if(s1.empty())
        {
            return true;
        }
        if(s2.empty() || s1.size() > s2.size())
        {
            return false;
        }
        
        vector<int> s1_map(128, 0);
        vector<int> s2_map(128, 0);
        
        for(unsigned int i = 0; i < s1.size(); ++i)
        {
            ++s1_map[s1[i]];
        }
        
        // 类似于一个滑动窗口截取子串
        for(unsigned int i = 0; i < s2.size(); ++i)
        {
            // 向右移动一位滑动窗口
            if(i >= s1.size())
            {
                --s2_map[s2[i-s1.size()]];
            }
            ++s2_map[s2[i]];
            
            if(s2_map == s1_map)
            {
                return true;
            }
        }
        
        return false;
    }
};
```

## Go
```go
func checkInclusion(s1 string, s2 string) bool {
    if len(s1) == 0 {
        return true
    }
    if len(s2) == 0 || len(s1) > len(s2) {
        return false
    }
    
    var s1_map [128]int
    var s2_map [128]int
    
    for _, c := range s1 {
        s1_map[c]++
    }
    
    for i, c := range s2 {
        if i >= len(s1) {
            s2_map[s2[i-len(s1)]]--
        }
        s2_map[c]++
        
        if s1_map == s2_map {
            return true
        }
    }
    
    return false
}
```