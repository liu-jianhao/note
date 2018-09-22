# 557. 反转字符串中的单词 III

## 题目
给定一个字符串，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。

```
示例 1:
输入: "Let's take LeetCode contest"
输出: "s'teL ekat edoCteeL tsetnoc" 
注意：在字符串中，每个单词由单个空格分隔，并且字符串中不会有任何额外的空格。
```


## 解题思路
思路很简单，就是找到句子中的每一个单词，然后逆序

### C++
```cpp
string reverseWords(string s) {
    if(s.empty())
        return s;
    
    string ret;
    int head = 0;
    
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == ' ')
        {
            string sub = s.substr(head, i-head);
            reverse(sub.begin(), sub.end());
            ret += sub;
            head = i + 1;
            ret += ' ';
        }
    }
    for(int i = s.size()-1; i >= head; i--)
    {
        ret += s[i];
    }
    return ret;
}
```


### Go
```go
func reverseWords(s string) string {
    b := []byte(s)
    var ret []byte
    head := 0

    for i := 0; i < len(b); i++ {
        if(b[i] == ' ') {
            for j := i-1; j >= head; j-- {
                ret = append(ret, b[j])
            }
            head = i + 1
            ret = append(ret, ' ')
        }
    }
    for i := len(b)-1; i >= head; i-- {
        ret = append(ret, b[i])
    }
    return string(ret)
}
```