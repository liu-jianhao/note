# 16. 最接近的三数之和

## 问题
给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
```
例如，给定数组 nums = [-1，2，1，-4], 和 target = 1.

与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).
```


## 解题思路
这道题与15题类似，只要将代码稍微改一下就能通过了。

增加一个变量`close`来记录最接近的值，每次不相等后指针移位之前都要与`close`来决定是否更新值。

```cpp
int threeSumClosest(vector<int>& nums, int target) {
    int res, close = INT_MAX;
    sort(nums.begin(),nums.end());
    
    for(int k = 0; k < nums.size(); ++k)
    {
        int i = k + 1;
        int j = nums.size() - 1;
        while(i < j){
            int value = nums[i] + nums[j];
            if(value > (target - nums[k]))
            {
                if(value + nums[k] - target < close)
                {
                    close = value + nums[k] - target;
                    res = value + nums[k];
                }
                --j;
            }
            else if(value < target - nums[k])
            {
                if(target - nums[k] - value < close)
                {
                    close = target - nums[k] - value;
                    res = value + nums[k];
                }
                ++i;
            }
            else
            {
                return target;
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