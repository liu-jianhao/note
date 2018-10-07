# 230. 二叉搜索树中第K小的元素

## 问题
给定一个二叉搜索树，编写一个函数 kthSmallest 来查找其中第 k 个最小的元素。

说明：
你可以假设 k 总是有效的，1 ≤ k ≤ 二叉搜索树元素个数。

```
示例 1:
输入: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
输出: 1
```
```
示例 2:

输入: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
输出: 3
```
进阶：
如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 k 小的值，你将如何优化 kthSmallest 函数？

## 解题思路
由于这是一棵二叉搜索树，所以它的中序遍历是排好序的，这是一个突破口。

然后想到了中序遍历的循环做法，可以用一个计数变量，当技术变量到k时，说明遍历到了第k个节点，而这个节点也就是第k小的节点。

```cpp
int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> stack;
    stack.push(root);
    int count = 0;
    TreeNode* p = root;
    
    while(p != nullptr || !stack.empty())
    {
        if(p != nullptr)
        {
            stack.push(p);
            p = p->left;
        }
        else
        {
            p = stack.top();
            stack.pop();
            
            if(++count == k)
            {
                return p->val;
            }
            
            p = p->right;
        }
    }
}
```