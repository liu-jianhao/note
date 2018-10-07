# 238. 除自身以外数组的乘积

## 问题
给定长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

```
示例:
输入: [1,2,3,4]
输出: [24,12,8,6]
说明: 请不要使用除法，且在 O(n) 时间复杂度内完成此题。
```
进阶：
你可以在常数空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组不被视为额外空间。）

## 解题思路
想了好久都没想出来，最后还是看了网上其它人的解法得到了启发。

解法就是用两个辅助数组，如数组N=[1,2,3,4]，我们一次遍历的时候，得到顺序的乘积为`order=[1,2,6,24]`，逆序的乘积为`reorder=[24, 24, 12, 4]`

那么最后对于数组N中的除当前元素之外其余各元素的乘积，我们就可以利用`order`和`reorder`这两个数组来计算得到，假设输出数组为ret，对于ret中的每一个元素，存在`ret[i] = order[i-1] * reorder[i+1]`（注意边界条件），最后得到的结果为`ret=[24, 12, 8, 6]`

```cpp
vector<int> productExceptSelf(vector<int>& nums) {
    if(nums.empty())
    {
        return vector<int>();
    }
    vector<int> order(nums.size());
    order[0] = nums[0];
    vector<int> reorder(nums.size());
    reorder[nums.size()-1] = nums[nums.size()-1];
    
    vector<int> ret(nums.size());
    
    int mul1 = nums[0], mul2 = nums[nums.size()-1];
    for(int i = 1; i < nums.size(); ++i)
    {
        mul1 *= nums[i];
        mul2 *= nums[nums.size()-i-1];
        order[i] = mul1;
        reorder[nums.size()-i-1] = mul2;
    }
    
    ret[0] = reorder[1];
    for(int i = 1; i < nums.size()-1; ++i)
    {
        ret[i] = order[i-1] * reorder[i+1];
    }
    ret[nums.size()-1] = order[nums.size()-2];
    
    return ret;
}
```