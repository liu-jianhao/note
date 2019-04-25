# 复原IP地址
给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。

示例:
```
输入: "25525511135"
输出: ["255.255.11.135", "255.255.111.35"]
```

## C++
```cpp
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        string ip;
        helper(s, 0, 0, ip, res);
        return res;
    }
    
    void helper(string s, int start, int partNum, string ip, vector<string>& res)
    {
        int len = s.size();
        if(len - start < 4-partNum || len - start > 3*(4-partNum))
            return;
        
        if(partNum == 4 && start == len)
        {
            // 把最后一个 '.' 去掉
            ip.erase(ip.end()-1, ip.end());
            res.push_back(ip);
            return;
        }
        
        int num = 0;
        for(int i = start; i < start+3; ++i)
        {
            num = num*10 + s[i] - '0';
            if(num < 256)
            {
                ip += s[i];
                helper(s, i+1, partNum+1, ip+'.', res);
            }
            if(num == 0)
                break;
        }
    }
};
```