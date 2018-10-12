# 78. 子集

## 问题

给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。

```
示例:
输入: nums = [1,2,3]
输出:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
```


## 解题思路
这是应用回溯算法的经典问题

### 方法一：二进制计数
这种方法理解起来较为简单，就是保存一个数组，每次遍历到一个新的数，用一个for循环来遍历这个数，
决定这个数出现还是不出现。
```cpp
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    // appears的每个值为1或0，说明第i个数是否出现在子集中
    vector<int> appears(nums.size());
    helper(res, appears, nums, 0);
    
    return res;
}

void helper(vector<vector<int>>& res, vector<int>& appears, vector<int>& nums, int count)
{
    // 所有数都已经遍历过了，即形成了一个子集
    if(count == nums.size())
    {
        vector<int> subres;
        for(int i = 0; i < nums.size(); ++i)
        {
            // 如果第i个数是1，则说明这个子集中第i个数出现，否则不出现
            if(appears[i])
            {
                subres.push_back(nums[i]);
            }
        }
        res.push_back(subres);
    }
    else
    {
        ++count;
        int c[2] = {0, 1};
        for(int i = 0; i < 2; ++i)
        {
            appears[count-1] = c[i];
            helper(res, appears, nums, count);
        }
    }
}
```
输出顺序
```
[[],[3],[2],[2,3],[1],[1,3],[1,2],[1,2,3]]
```


### 方法二：顺序法
```cpp
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> part;
    res.push_back(part);
    helper(res, part, nums, 0);
    
    return res;
}

void helper(vector<vector<int>>& res, vector<int>& part, vector<int> nums, int start)
{
    for(int i = start; i < nums.size(); ++i)
    {
        part.push_back(nums[i]);
        res.push_back(part);
        helper(res, part, nums, i+1);
        part.pop_back();
    }
}
```

输出顺序
```
[[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]
```