# 215. 数组中的第K个最大元素

## 问题

在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
```
示例 1:
输入: [3,2,1,5,6,4] 和 k = 2
输出: 5
```
```
示例 2:
输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4
```
说明:
你可以假设 k 总是有效的，且 1 ≤ k ≤ 数组的长度。

## 解题思路
首先想到的方法是直接将数组从大到小排序，然后返回第k个元素即可。
```cpp
int findKthLargest(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end(), greater<int>());
    
    return nums[k-1];
}
```

第二种做法是用一个multiset来保存目前遍历到的k个最大的数，每遍历到一个大于multiset中最小元素的元素就插入集合，由于集合是排好序的，所以可以很快取得集合中最小值。
```cpp
int findKthLargest(vector<int>& nums, int k) {
    multiset<int> s;
    
    for(int i = 0; i < nums.size(); ++i)
    {
        if(s.size() < k)
        {
            s.insert(nums[i]);
        }
        else if(nums[i] > *(s.begin()))
        {
            s.erase(s.begin());
            s.insert(nums[i]);
        }
    }
    
    return *(s.begin());
}
```