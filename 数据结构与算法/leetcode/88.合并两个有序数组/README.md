# 88. 合并两个有序数组

## 问题
给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。
```
说明:
初始化 nums1 和 nums2 的元素数量分别为 m 和 n。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
```
```
示例:
输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3
输出: [1,2,2,3,5,6]
```

## 解题思路
与之前有序链表的合并类似

### C++
```cpp
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    if(nums1.empty())
        nums1 = nums2;
    if(nums2.empty())
        return;
    
    int cur1 = m-1;
    int cur2 = n-1;
    int end = m + n - 1;
    
    while(cur2 >= 0)
    {
        // 注意这个cur1！=-1这个条件
        if(cur1 != -1 && nums2[cur2] < nums1[cur1])
        {
            nums1[end--] = nums1[cur1--];
        }
        else
        {
            nums1[end--] = nums2[cur2--];
        }
    }
}
```

### Go
```go
func merge(nums1 []int, m int, nums2 []int, n int)  {
    if m <= 0 {
        for i, n := range nums2 {
            nums1[i] = n
        }
    }
    if n <= 0 {
        return
    }
    
    cur1 := m-1
    cur2 := n-1
    end := m+n-1
    
    for cur2 >= 0 {
        if cur1 != -1 && nums2[cur2] < nums1[cur1] {
            nums1[end] = nums1[cur1]
            end--
            cur1--
        } else {
            nums1[end] = nums2[cur2]
            end--
            cur2--
        }
    }
}
```