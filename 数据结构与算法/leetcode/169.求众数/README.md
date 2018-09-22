# 169. 求众数

## 题目
给定一个大小为 n 的数组，找到其中的众数。众数是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在众数。

```
示例 1:
输入: [3,2,3]
输出: 3
```

```
示例 2:
输入: [2,2,1,1,1,2,2]
输出: 2
```


## 解题思路
我们只要用一个计数器和一个候选人，只要迭代到的值和候选人一样，计数器就加一，否则计数器减一，当计数器为零时，更换候选人。这样就能找到众数

### C++
```cpp
int majorityElement(vector<int>& nums) {
    int res;
    int times = 0;
    for(int n : nums) {
        if(times == 0) {
            res = n;
            ++times;
        } else if (res == n){
            ++times;
        } else {
            --times;
        }
    }
    
    return res;
}
```

### Go
```go
func majorityElement(nums []int) int {
    res := 0
    times := 0
    for _, n := range nums {
        if times == 0 {
            res = n
            times = 1
        } else if res == n {
            times++
        } else {
            times--
        }
    }
    
    return res
}
```