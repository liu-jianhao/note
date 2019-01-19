// 面试题54：二叉搜索树的第k个结点
// 题目：给定一棵二叉搜索树，请找出其中的第k大的结点。


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

class Solution {
public:
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        if(pRoot == nullptr)
        {
            return nullptr;
        }
        TreeNode* p = pRoot;
        
        return  KthNodeCore(p, k);
    }

    TreeNode* KthNodeCore(TreeNode* p, int& k)
    {
        TreeNode* res = nullptr;
        
        if(p->left != nullptr)
        {
            res = KthNodeCore(p->left, k);
        }
        
        if(res == nullptr && --k == 0)
        {
            res = p;
        }
        
        // 要注意添加res==nullptr的判断
        if(res == nullptr && p->right != nullptr)
        {
            res = KthNodeCore(p->right, k);
        }
        
        return res;
    }
};