# 104. 二叉树的最大深度

## 题目
给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

说明: 叶子节点是指没有子节点的节点。

```
示例：
给定二叉树 [3,9,20,null,null,15,7]，

    3
   / \
  9  20
    /  \
   15   7
返回它的最大深度 3
```


## 解决思路
有关树的问题第一个想到的就是要使用递归，既然要求树的最大深度，那必然要比较是左子树的深度还是右子树的深度，只要每次递归深度加一，而递归的停止条件是已经到叶子树节点的下一个(NULL)了

### C++
```cpp
int maxDepth(TreeNode* root) {
    if(root == NULL)
        return 0;
    
    int leftDepth, rightDepth;
    leftDepth = rightDepth = 1;
    leftDepth += maxDepth(root->left);
    rightDepth += maxDepth(root->right);
    
    return leftDepth > rightDepth ? leftDepth : rightDepth;
}
```

### Go
```go
func maxDepth(root *TreeNode) int {
    if root  == nil {
        return 0
    }

    leftDepth := 1
    rightDepth := 1
    leftDepth += maxDepth(root.Left)
    rightDepth += maxDepth(root.Right)
    
    if rightDepth > leftDepth {
        return rightDepth
    } else {
        return leftDepth
    }
}
```