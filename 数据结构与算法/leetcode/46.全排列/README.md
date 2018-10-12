# 46.全排列

## 问题
给定一个没有重复数字的序列，返回其所有可能的全排列。
```
示例:
输入: [1,2,3]
输出:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
```


## 解题思路
与求子集的那道题类似，都用到了回溯算法。

```cpp
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> temp;
    backtrack(nums, temp, res); 
    
    return res;
}

void backtrack(vector<int>& nums, vector<int>& temp, vector<vector<int> >& res)
{    
    if(temp.size() == nums.size())
    {
        res.push_back(temp);
        return;
    }
    else{
        for(int i = 0; i < nums.size(); i++)
        {
            vector<int>::iterator result = find(temp.begin(),temp.end(),nums[i]);
            if(result == temp.end())
            {
                temp.push_back(nums[i]);
                backtrack(nums, temp, res);
                temp.pop_back();
            }
        }  
    } 
}
```