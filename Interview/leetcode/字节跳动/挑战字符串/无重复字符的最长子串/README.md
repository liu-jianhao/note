# 无重复子串
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:
```
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
```

示例 2:
```
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
```

示例 3:
```
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
```

## C++
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.empty())
        {
            return 0;
        }
        
        vector<int> map(128, -1);
        
        int current = 0;
        int longest = 0;
        
        for(unsigned i = 0; i < s.size(); ++i)
        {
            if(map[s[i]] == -1 || i - current > map[s[i]])
            {
                current++;
            }
            else
            {
                if(current > longest)
                {
                    longest = current;
                }
                current = i - map[s[i]];
            }
            map[s[i]] = i;
        }
        
        if(current > longest)
        {
            longest = current;
        }

        return longest; 
    }
};
```

## golang
```go
func lengthOfLongestSubstring(s string) int {
    var lastAppear [128]int
    
    for _, c := range s {
        lastAppear[c] = -1
    }
    
    current := 0
    longest := 0
    
    for i, c := range s {
        if lastAppear[c] == -1 || i - current > lastAppear[c] {
            current += 1
        } else {
            if(current > longest) {
                longest = current
            }
            current = i - lastAppear[c]
        }
        lastAppear[c] = i
    }

    if(current > longest) {
        longest = current
    }
    
    return longest
}
```