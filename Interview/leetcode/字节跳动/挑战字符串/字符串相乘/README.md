# 字符串相乘

给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

示例 1:
```
输入: num1 = "2", num2 = "3"
输出: "6"
```

示例 2:
```
输入: num1 = "123", num2 = "456"
输出: "56088"
```

说明：
num1 和 num2 的长度小于110。
num1 和 num2 只包含数字 0-9。
num1 和 num2 均不以零开头，除非是数字 0 本身。
不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。

## C++
```cpp
class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1.empty() || num2.empty())
        {
            return "";
        }
        
        int l1 = num1.size();
        int l2 = num2.size();
        int k = l1 + l2 - 2;
        
        int carryBit = 0;
        vector<int> tmpres(l1 + l2);
        
        for(int i = 0; i < l1; ++i)
        {
            for(int j = 0; j < l2; ++j)
            {
                tmpres[k - i - j] += (num1[i] - '0') * (num2[j] - '0');
            }
        }
        
        for(int i = 0; i < l1 + l2; ++i)
        {
            tmpres[i] += carryBit;
            carryBit = tmpres[i] / 10;
            tmpres[i] %= 10;
        }
        
        int i = k + 1;
        while(tmpres[i] == 0)
        {
            --i;
        }
        if(i < 0)
        {
            return "0";
        }
        string res;
        for(; i >= 0; --i)
        {
            res.push_back(tmpres[i] + '0');
        }
        
        return res;
    }
};
```

## Go
```go
func multiply(num1 string, num2 string) string {
    if len(num1) == 0 || len(num2) == 0 {
        return ""
    }
    
    l1 := len(num1)
    l2 := len(num2)
    k := l1 + l2 - 2;
    
    carryBit := 0
    
    var tmpres [220]int

    for i := 0; i < l1; i++ {
        for j := 0; j < l2; j++ {
            n1, _ := strconv.Atoi(num1[i])
            n2, _ := strconv.Atoi(num2[i])
            tmpres[k-i-j] += n1 * n2
        }
    }
    
    for i := 0; i < l1 + l2; i++ {
        tmpres[i] += carryBit
        carryBit = tmpres[i] / 10
        tmpres[i] = tmpres[i] % 10
    }
    
    i := k + 1
    for tmpres[i] == 0 {
        i--
    }
    if i < 0 {
        return "0"
    }
    
    res := ""
    for ; i >= 0; i-- {
        res += string(tmpres[i])
    }
    
    return res
}
```