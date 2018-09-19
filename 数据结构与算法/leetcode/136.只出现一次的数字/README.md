# 136. 只出现一次的数字

## 题目
给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

说明：
你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？

示例 1:
输入: [2,2,1]
输出: 1

示例 2:
输入: [4,1,2,1,2]
输出: 4


## 解题思路
这道题使用位运算最为简单，两个相同的数异或结果是0，那么由于该数组只有一个元素出现一次，其他都出现了两次，那么只要将全部元素异或就能得到那个只出现一次的元素

### C++
```cpp
int singleNumber(vector<int>& nums) {
    int res = nums[0];
    
    for(auto it = nums.begin()+1; it != nums.end(); it++) {
        res ^= *it;
    }
    return res;
}
```

### Go
```go
func singleNumber(nums []int) int {
    res := nums[0]
    
    for i := 1; i < len(nums); i++ {
        res ^= nums[i]
    }
    return res
}
```