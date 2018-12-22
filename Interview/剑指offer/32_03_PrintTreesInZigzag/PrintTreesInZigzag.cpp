// 面试题32（三）：之字形打印二叉树
// 题目：请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺
// 序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，
// 其他行以此类推。



struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(nullptr), right(nullptr) {
    }
};

class Solution {
public:
    vector<vector<int> > Print(TreeNode* pRoot) {
        vector<vector<int>> result;
        vector<int> sub;
        if(pRoot == nullptr)
        {
            return result;
        }
        
        stack<TreeNode*> s1;
        stack<TreeNode*> s2;
        s1.push(pRoot);
        
        while(!s1.empty() || !s2.empty())
        {
            while(!s1.empty())
            {
                TreeNode* tmp = s1.top();
                sub.push_back(tmp->val);
                s1.pop();
                if(tmp->left != nullptr)
                {
                    s2.push(tmp->left);
                }
                if(tmp->right != nullptr)
                {
                    s2.push(tmp->right);
                }
            }
            
            if(!sub.empty())
            {
                result.push_back(sub);
                sub.clear();
            }
            
            
            while(!s2.empty())
            {
                TreeNode* tmp = s2.top();
                sub.push_back(tmp->val);
                s2.pop();
                if(tmp->right != nullptr)
                {
                    s1.push(tmp->right);
                }
                if(tmp->left != nullptr)
                {
                    s1.push(tmp->left);
                }
            }
            
            if(!sub.empty())
            {
                result.push_back(sub);
                sub.clear();
            }
        }
        
        return result;
    }
    
};