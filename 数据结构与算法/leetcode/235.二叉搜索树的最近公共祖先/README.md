# 235. 二叉搜索树的最近公共祖先

## 问题描述
给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]
```
        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5
```
```
示例 1:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6 
解释: 节点 2 和节点 8 的最近公共祖先是 6。
```

```
示例 2:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。
```

说明:
+ 所有节点的值都是唯一的。
+ p、q 为不同节点且均存在于给定的二叉搜索树中。


## 解题思路
这是一棵二叉搜索树，那就可以利用二叉搜索树的性质，且所有节点的值是唯一的，那么我们可以分为以下4种情况：
1. `p`、`q`都小于`root`节点中的值，那么`p`和`q`就都在`root`的左子树
2. 同理，都大于则在右子树
3. 如果是一大一小，那么`p`和`q`则分别在`root`的左右子树，那么`root`就是它们的共同祖先
4. `root`节点的值与`p`或`q`中的某一个值相等，那么相等的那个节点就是另一个的祖先


### C++
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root && p && q) {
        if(root->val == p->val) {
            return p;
        } else if(root->val == q->val) {
            return q;
        } else if(root->val < p->val && root->val > q->val ||
                    root->val > p->val && root->val < q->val) {
            return root;
        } else if(root->val < p->val && root->val < q->val) {
            return lowestCommonAncestor(root->right, p, q);
        } else if(root->val > p->val && root->val > q->val) {
            return lowestCommonAncestor(root->left, p, q);
        }
    }
}
```