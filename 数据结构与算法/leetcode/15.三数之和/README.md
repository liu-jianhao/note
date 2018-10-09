# 15. 三数之和

## 问题
给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
满足要求的三元组集合为：
```
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

## 解题思路
首先想到的方法是暴力破解法，就是每个情况都遍历到，先固定一个值，然后再用两个指针找另外两个值。

如果直接就开始暴力破解那么效率会很低，既然是和大小有关，那么就想到要先将数组排序，这样效率就更高一些，而且两个指针分别指向除固定值之外的头和尾。

最后一个难点就是想怎么去重。一开始我直接用标准库中的算法unique，但这样做会有一个问题，如果是[0, 0, 0]这种情况就会有问题，所以要换一种方式去重。

可以用更简单直接的方法去重，因为数组是排好序的，每次找到一组答案需要移动指针，头指针向后移动一位，尾指针向前移动一位，移位后如果仍然相等就继续移位。

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(),nums.end());
    vector<int> v;
    
    for(int k = 0; k < nums.size(); ++k)
    {
        int i = k + 1;
        int j = nums.size() - 1;
        while(i < j){
            int value = nums[i] + nums[j];
            if(value > (0-nums[k]))
            {
                --j;
            }
            else if(value < 0-nums[k])
            {
                ++i;
            }
            else
            {
                v.push_back(nums[k]);
                v.push_back(nums[i]);
                v.push_back(nums[j]);
                res.push_back(v);
                v.clear();
                // 去重
                while(i < j && nums[i] == nums[i+1])
                {
                    ++i;
                }
                while(i < j && nums[j] == nums[j-1])
                {
                    --j;
                }
                ++i;
                --j;
            }                
        }
        // 去重
        while(k < nums.size()-1 && nums[k] == nums[k+1])
        {
            ++k;
        }
    }
    return res;
}
```