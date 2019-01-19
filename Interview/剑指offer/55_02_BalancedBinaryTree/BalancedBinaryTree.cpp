// 面试题55（二）：平衡二叉树
// 题目：输入一棵二叉树的根结点，判断该树是不是平衡二叉树。如果某二叉树中
// 任意结点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。

class Solution {
public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
        if(pRoot == nullptr)
        {
            return true;
        }
        
        int depth;
        return IsBalanced_Solution(pRoot, depth);
    }
    
    bool IsBalanced_Solution(TreeNode* pRoot, int& depth)
    {
        if(pRoot == nullptr)
        {
            depth = 0;
            return true;
        }
        
        int left, right;
        if(IsBalanced_Solution(pRoot->left, left) && IsBalanced_Solution(pRoot->right, right))
        {
            int diff = abs(left - right);
            if(diff <= 1)
            {
                depth = std::max(left, right) + 1;
                return true;
            }
        }
        
        return false;
    }
};