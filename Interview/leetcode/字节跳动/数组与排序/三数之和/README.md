# 三数之和
给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]

## C++
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if(nums.size() < 3)
            return res;
        
        sort(nums.begin(), nums.end());
        
        vector<int> subRes(3);
        for(int a = 0; a < nums.size(); ++a)
        {
            int b = a + 1;
            int c = nums.size()-1;
            while(b < c)
            {
                int sum = nums[a] + nums[b] + nums[c];
                if(sum < 0)
                    ++b;
                else if(sum > 0)
                    --c;
                else
                {
                    subRes[0] = nums[a];
                    subRes[1] = nums[b];
                    subRes[2] = nums[c];
                    res.push_back(subRes);
                    
                    // 要注意去重
                    while(b < c && nums[b] == nums[b+1])
                        ++b;
                    while(b < c && nums[c] == nums[c-1])
                        --c;
                    // 别忘了还要调整指针
                    ++b;
                    --c;
                }
            }
            while(a < nums.size()-1 && nums[a] == nums[a+1])
                ++a;
        }
        return res;
    }
};
```